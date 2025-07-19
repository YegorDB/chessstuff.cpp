#include <stdexcept>

#include "handler.h"

Handler::Handler(const FEN& fen) {
    _initState(fen);
    _setActions();
};

Handler::Handler() : Handler(FEN{FEN::INITIAL_POSITION}) {};

void Handler::_initState(const FEN& fen) {
    _state = fen.getState();
};

const ActionsPlaces& Handler::getActionsPlaces() {
    return _actionsPlaces;
};

const State& Handler::getState() {
    return _state;
};

Handler::Response Handler::move(const Point& from, const Point& to) {
    if (!from.isValid() || !to.isValid()) {
        return Response{Response::Status::INVALID_POINT};
    } else if (!_state.piecePlaces.contains(from)) {
        return Response{Response::Status::PIECE_DOES_NOT_EXIST};
    } else if (!_state.piecePlaces.getPiece(from).hasColor(_state.activeColor)) {
        return Response{Response::Status::WRONG_PIECE_COLOR};
    } else if (!_state.piecePlaces.contains(to) && !_actionsPlaces.getActions(from).get(ActionType::PLACE).get(ActionRelation::TO).contains(to)) {
        return Response{Response::Status::WRONG_DESTINATION};
    } else if (_state.piecePlaces.contains(to) && !_actionsPlaces.getActions(from).get(ActionType::THREAT).get(ActionRelation::TO).contains(to)) {
        return Response{Response::Status::WRONG_DESTINATION};
    }

    _state.piecePlaces.move(from, to);
    if (_state.activeColor == PieceColor::WHITE) {
        _state.activeColor = PieceColor::BLACK;
    } else if (_state.activeColor == PieceColor::BLACK) {
        _state.activeColor = PieceColor::WHITE;
        _state.movesCount++;
    }
    _setActions();
    return Response{Response::Status::OK};
};

Handler::Response::Response(Status status) : status(status) {};

bool Handler::Response::isOk() {
    return status == Status::OK;
};

void Handler::_setActions() {
    /*
    Active color piece has
    - squares without pieces to place to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to

    Inactive color piece has
    - squares without pieces to threat to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to
    */

    _actionsPlaces.clearActions();
    std::vector<Point> bindedPoints;
    _setBaseActions(bindedPoints);
    _restrictKingActions();
};

void Handler::_setBaseActions(std::vector<Point>& bindedPoints) {
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (piece.hasColor(_state.activeColor)) {
            for (Direction direction : piece.getPlaceDirections()) {
                for (Point* nextPoint : Board::pointsByDirection(point, direction)) {
                    if (_state.piecePlaces.contains(*nextPoint)) {
                        break;
                    }
                    _actionsPlaces.setAction(ActionType::PLACE, point, *nextPoint);
                }
            }
        }

        for (Direction direction : piece.getThreatDirections()) {
            Point prevPoint;
            Point prevPointWithPiece;
            for (Point* nextPoint : Board::pointsByDirection(point, direction)) {
                if (!_state.piecePlaces.contains(*nextPoint)) {
                    if (!piece.hasColor(_state.activeColor) && prevPointWithPiece.isUndefined()) {
                        _actionsPlaces.setAction(ActionType::THREAT, point, *nextPoint);
                    } else if (!prevPoint.isUndefined()) {
                        _threatSquareAfterKingIfNeeded(point, prevPoint, *nextPoint);
                    }

                    prevPoint = *nextPoint;
                    continue;
                }
                if (!prevPointWithPiece.isUndefined()) {
                    _actionsPlaces.setAction(ActionType::XRAY, point, *nextPoint);
                    _bindPieceIfNeeded(point, prevPointWithPiece, *nextPoint, bindedPoints);
                    _supportPieceAfterKingIfNeeded(point, prevPointWithPiece, *nextPoint);
                    break;
                }
                const Piece& nextPiece = _state.piecePlaces.getPiece(*nextPoint);
                if (piece.hasSameColor(nextPiece)) {
                    _actionsPlaces.setAction(ActionType::SUPPORT, point, *nextPoint);
                } else {
                    _actionsPlaces.setAction(ActionType::THREAT, point, *nextPoint);
                }
                prevPoint = *nextPoint;
                prevPointWithPiece = *nextPoint;
            }
        }
    }
};

void Handler::_restrictKingActions() {
    Point activeKingPoint = Point{};
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (piece.isKing() && piece.hasColor(_state.activeColor)) {
            activeKingPoint = point;
            break;
        }
    }

    if (activeKingPoint.isUndefined()) {
        throw std::runtime_error{"Missed active king."};
    }

    const Actions& activeKingActions = _actionsPlaces.getActions(activeKingPoint);

    PointSet placeToPointsToErase;
    for (const Point& point : activeKingActions.get(ActionType::PLACE).get(ActionRelation::TO)) {
        const Actions& nextSquareActions = _actionsPlaces.getActions(point);
        if (!nextSquareActions.get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
            placeToPointsToErase.insert(point);
        }
    }
    _actionsPlaces.erasePoints(activeKingPoint, ActionType::PLACE, ActionRelation::TO, placeToPointsToErase);

    PointSet threatToPointsToErase;
    for (const Point& point : activeKingActions.get(ActionType::THREAT).get(ActionRelation::TO)) {
        const Actions& nextSquareActions = _actionsPlaces.getActions(point);
        if (!nextSquareActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty()) {
            threatToPointsToErase.insert(point);
        }
    }
    _actionsPlaces.erasePoints(activeKingPoint, ActionType::THREAT, ActionRelation::TO, threatToPointsToErase);
};

/**
 * Example:
 * Black queen bind white bishop before white king
 *  _____ _____ _____ _____
 * |    *|     |    *|     |
 * |  Q  |     |  B  |  K  |
 * |_____|_____|_____|_____|
 */
void Handler::_bindPieceIfNeeded(const Point& point, const Point& prevPointWithPiece, const Point& nextPoint, std::vector<Point>& bindedPoints) {
    if (!_state.piecePlaces.contains(point) || !_state.piecePlaces.contains(prevPointWithPiece) || !_state.piecePlaces.contains(nextPoint)) {
        return;
    }

    const Piece& piece = _state.piecePlaces.getPiece(point);
    const Piece& prevPiece = _state.piecePlaces.getPiece(prevPointWithPiece);
    const Piece& nextPiece = _state.piecePlaces.getPiece(nextPoint);

    if (nextPiece.isKing() && nextPiece.hasSameColor(prevPiece) && !nextPiece.hasSameColor(piece)) {
        bindedPoints.push_back(prevPointWithPiece);
        _actionsPlaces.setAction(ActionType::BIND, point, prevPointWithPiece);
    }
};

/**
 * Example:
 * Black rook threat square after white king
 *  _____ _____ _____ _____
 * |    *|     |     |    *|
 * |  r  |     |  K  |     |
 * |_____|_____|_____|_____|
 */
void Handler::_threatSquareAfterKingIfNeeded(const Point& point, const Point& prevPoint, const Point& nextPoint) {
    if (!_state.piecePlaces.contains(point) || !_state.piecePlaces.contains(prevPoint) || _state.piecePlaces.contains(nextPoint)) {
        return;
    }

    const Piece& piece = _state.piecePlaces.getPiece(point);
    const Piece& prevPiece = _state.piecePlaces.getPiece(prevPoint);

    if (!piece.hasColor(_state.activeColor) && prevPiece.isKing() && !piece.hasSameColor(prevPiece)) {
        _actionsPlaces.setAction(ActionType::THREAT, point, nextPoint);
    }
};

/**
 * Example:
 * White rook suport white knight after black king
 *  _____ _____ _____ _____
 * |    *|     |     |    *|
 * |  R  |     |  k  |  N  |
 * |_____|_____|_____|_____|
 */
void Handler::_supportPieceAfterKingIfNeeded(const Point& point, const Point& prevPointWithPiece, const Point& nextPoint) {
    if (!_state.piecePlaces.contains(point) || !_state.piecePlaces.contains(prevPointWithPiece) || !_state.piecePlaces.contains(nextPoint)) {
        return;
    }

    const Piece& piece = _state.piecePlaces.getPiece(point);
    const Piece& prevPiece = _state.piecePlaces.getPiece(prevPointWithPiece);
    const Piece& nextPiece = _state.piecePlaces.getPiece(nextPoint);

    if (!piece.hasColor(_state.activeColor) && prevPiece.isKing() && !piece.hasSameColor(prevPiece) && piece.hasSameColor(nextPiece)) {
        _actionsPlaces.setAction(ActionType::SUPPORT, point, nextPoint);
    }
};
