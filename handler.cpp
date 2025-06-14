#include <stdexcept>

#include "handler.h"

Handler::Handler(const FEN& fen) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            _actionsPlaces[Point{x, y}] = Actions{};
        }
    }
    _initState(fen);
    _clearActions();
    _setActions();
};

Handler::Handler() : Handler(FEN{FEN::INITIAL_POSITION}) {};

void Handler::_initState(const FEN& fen) {
    _state = fen.getState();
};

const ActionsPlaces& Handler::getActionsPlaces() {
    return _actionsPlaces;
};

Board& Handler::getBoard() {
    return _board;
};

const State& Handler::getState() {
    return _state;
};

void Handler::_clearActions() {
    for (auto& [point, actions] : _actionsPlaces) {
        actions.clear();
    }
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

    std::vector<Point> bindedPoints;
    _setBaseActions(bindedPoints);
    _restrictKingActions();
};

void Handler::_setBaseActions(std::vector<Point>& bindedPoints) {
    for (const auto& [point, piece] : _state.piecePlaces) {
        if (piece.hasColor(_state.activeColor)) {
            for (Direction direction : piece.getPlaceDirections()) {
                for (Square* nextSquare : _board.squaresByDirection(point, direction)) {
                    const Point& nextPoint = nextSquare->point;
                    if (_state.piecePlaces.contains(nextPoint)) {
                        break;
                    }
                    _setAction(ActionType::PLACE, point, nextPoint);
                }
            }
        }

        for (Direction direction : piece.getThreatDirections()) {
            Square* prevSquare = nullptr;
            Square* prevSquareWithPiece = nullptr;
            for (Square* nextSquare : _board.squaresByDirection(point, direction)) {
                const Point& nextPoint = nextSquare->point;
                if (!_state.piecePlaces.contains(nextPoint)) {
                    if (!piece.hasColor(_state.activeColor) && prevSquareWithPiece == nullptr) {
                        _setAction(ActionType::THREAT, point, nextPoint);
                    } else if (prevSquare != nullptr) {
                        _threatSquareAfterKingIfNeeded(point, prevSquare->point, nextPoint);
                    }

                    prevSquare = nextSquare;
                    continue;
                }
                if (prevSquareWithPiece != nullptr) {
                    _setAction(ActionType::XRAY, point, nextPoint);
                    _bindPieceIfNeeded(point, prevSquareWithPiece->point, nextPoint, bindedPoints);
                    _supportPieceAfterKingIfNeeded(point, prevSquareWithPiece->point, nextPoint);
                    break;
                }
                const Piece& nextPiece = _state.piecePlaces.at(nextPoint);
                if (piece.hasSameColor(nextPiece)) {
                    _setAction(ActionType::SUPPORT, point, nextPoint);
                } else {
                    _setAction(ActionType::THREAT, point, nextPoint);
                }
                prevSquare = nextSquare;
                prevSquareWithPiece = nextSquare;
            }
        }
    }
};

void Handler::_restrictKingActions() {
    Point activeKingPoint = Point{};
    for (const auto& [point, piece] : _state.piecePlaces) {
        if (piece.isKing() && piece.hasColor(_state.activeColor)) {
            activeKingPoint = point;
            break;
        }
    }

    if (activeKingPoint.isUndefined()) {
        throw std::runtime_error{"Missed active king."};
    }

    Actions& activeKingActions = _actionsPlaces[activeKingPoint];

    PointSet placeToPointsCopy;
    for (const Point& point : activeKingActions.get(ActionType::PLACE).get(ActionRelation::TO)) {
        placeToPointsCopy.insert(point);
    }

    for (const Point& point : placeToPointsCopy) {
        const Actions& nextSquareActions = _actionsPlaces.at(point);
        if (!nextSquareActions.get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
            activeKingActions.erase(ActionType::PLACE, ActionRelation::TO, point);
        }
    }

    PointSet threatToPointsCopy;
    for (const Point& point : activeKingActions.get(ActionType::THREAT).get(ActionRelation::TO)) {
        threatToPointsCopy.insert(point);
    }

    for (const Point& point : threatToPointsCopy) {
        const Actions& nextSquareActions = _actionsPlaces.at(point);
        if (!nextSquareActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty()) {
            activeKingActions.erase(ActionType::THREAT, ActionRelation::TO, point);
        }
    }
};

void Handler::_setAction(ActionType type, const Point& byPoint, const Point& toPoint) {
    if (!byPoint.isValid() || !toPoint.isValid()) {
        throw std::runtime_error{"Wrong point."};
    }
    _actionsPlaces[byPoint].insert(type, ActionRelation::TO, toPoint);
    _actionsPlaces[toPoint].insert(type, ActionRelation::BY, byPoint);
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

    const Piece& piece = _state.piecePlaces.at(point);
    const Piece& prevPiece = _state.piecePlaces.at(prevPointWithPiece);
    const Piece& nextPiece = _state.piecePlaces.at(nextPoint);

    if (nextPiece.isKing() && nextPiece.hasSameColor(prevPiece) && !nextPiece.hasSameColor(piece)) {
        bindedPoints.push_back(prevPointWithPiece);
        _setAction(ActionType::BIND, point, prevPointWithPiece);
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

    const Piece& piece = _state.piecePlaces.at(point);
    const Piece& prevPiece = _state.piecePlaces.at(prevPoint);

    if (!piece.hasColor(_state.activeColor) && prevPiece.isKing() && !piece.hasSameColor(prevPiece)) {
        _setAction(ActionType::THREAT, point, nextPoint);
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

    const Piece& piece = _state.piecePlaces.at(point);
    const Piece& prevPiece = _state.piecePlaces.at(prevPointWithPiece);
    const Piece& nextPiece = _state.piecePlaces.at(nextPoint);

    if (!piece.hasColor(_state.activeColor) && prevPiece.isKing() && !piece.hasSameColor(prevPiece) && piece.hasSameColor(nextPiece)) {
        _setAction(ActionType::SUPPORT, point, nextPoint);
    }
};
