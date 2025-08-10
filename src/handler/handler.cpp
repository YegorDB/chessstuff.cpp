#include <stdexcept>

#include "handler.h"

Handler::Handler(const FEN& fen) {
    _initState(fen);
    _actionsPlaces.clearActions();
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
    } else if (!_state.pawnPromotion.isUndefined()) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION};
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
    _actionsPlaces.clearActions();
    const Piece& toPiece = _state.piecePlaces.getPiece(to);
    if (toPiece.isPawn() && _isPawnOnPromotionRow(to, toPiece.isWhiteColor())) {
        _state.pawnPromotion = to;
    } else {
        _endMove();
    }

    return Response{Response::Status::OK};
};

Handler::Response Handler::promotePawn(PieceType pieceType) {
    if (_state.pawnPromotion.isUndefined()) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION};
    } else if (!Piece::PAWN_PROMOTION_TYPES.contains(pieceType)) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION_PIECE_TYPE};
    }

    bool isWhiteColor = _state.activeColor == PieceColor::WHITE;
    Piece piece{pieceType, isWhiteColor};
    _state.piecePlaces.place(_state.pawnPromotion, piece);

    _state.pawnPromotion = Point{};
    _endMove();

    return Response{Response::Status::OK};
};

Handler::Response::Response(Status status) : status(status) {};

bool Handler::Response::isOk() {
    return status == Status::OK;
};

void Handler::_endMove() {
    if (_state.activeColor == PieceColor::WHITE) {
        _state.activeColor = PieceColor::BLACK;
    } else if (_state.activeColor == PieceColor::BLACK) {
        _state.activeColor = PieceColor::WHITE;
        _state.movesCount++;
    }
    _setActions();
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
    _setPawnJumpMoves();
    const Point& kingPoint = _getActiveKingPoint();
    _restrictKingActions(kingPoint);
    _restrictBindedWithKingPiecesActions(kingPoint, bindedPoints);
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

const Point& Handler::_getActiveKingPoint() const {
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (piece.isKing() && piece.hasColor(_state.activeColor)) {
            return point;
        }
    }
    throw std::runtime_error{"Missed active king."};
}

void Handler::_restrictKingActions(const Point& kingPoint) {
    const Actions& kingActions = _actionsPlaces.getActions(kingPoint);

    _eraseKingActions(ActionType::PLACE, ActionType::THREAT, kingPoint, kingActions);
    _eraseKingActions(ActionType::THREAT, ActionType::SUPPORT, kingPoint, kingActions);
};

void Handler::_eraseKingActions(
    ActionType actionType,
    ActionType restrictActionType,
    const Point& kingPoint,
    const Actions& kingActions
) {
    PointSet pointsToErase;
    for (const Point& p : kingActions.get(actionType).get(ActionRelation::TO)) {
        const Actions& nextSquareActions = _actionsPlaces.getActions(p);
        if (!nextSquareActions.get(restrictActionType).get(ActionRelation::BY).empty()) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(kingPoint, actionType, ActionRelation::TO, pointsToErase);
}

void Handler::_restrictBindedWithKingPiecesActions(const Point& kingPoint, const std::vector<Point>& bindedPoints) {
    for (const Point& point : bindedPoints) {
        const Actions& pieceActions = _actionsPlaces.getActions(point);

        const PointSet& bindByPoints = pieceActions.get(ActionType::BIND).get(ActionRelation::BY);
        if (bindByPoints.size() != 1) {
            throw std::runtime_error{"Wrong bind by points set size."};
        }
        const Point& bindByPoint = *(bindByPoints.begin());

        PointSet awaliablePoints;
        for (Point* p : Board::pointsByTwoPoints(kingPoint, bindByPoint)) {
            awaliablePoints.insert(Point{p->x(), p->y()});
        }

        _eraseBindedWithKingPiecesActions(ActionType::PLACE, point, pieceActions, awaliablePoints);
        _eraseBindedWithKingPiecesActions(ActionType::THREAT, point, pieceActions, awaliablePoints);
    }
};

void Handler::_eraseBindedWithKingPiecesActions(
    ActionType actionType,
    const Point& point,
    const Actions& pieceActions,
    const PointSet& awaliablePoints
) {
    PointSet pointsToErase;
    for (const Point& p : pieceActions.get(actionType).get(ActionRelation::TO)) {
        if (!awaliablePoints.contains(p)) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(point, actionType, ActionRelation::TO, pointsToErase);
};

/**
 * Example:
 * Black queen bind white bishop before white king
 *  _____ _____ _____ _____
 * |    *|     |    *|     |
 * |  q  |     |  B  |  K  |
 * |_____|_____|_____|_____|
 */
void Handler::_bindPieceIfNeeded(const Point& point, const Point& prevPointWithPiece, const Point& nextPoint, std::vector<Point>& bindedPoints) {
    if (!_state.piecePlaces.contains(point) || !_state.piecePlaces.contains(prevPointWithPiece) || !_state.piecePlaces.contains(nextPoint)) {
        return;
    }

    const Piece& piece = _state.piecePlaces.getPiece(point);
    const Piece& prevPiece = _state.piecePlaces.getPiece(prevPointWithPiece);
    const Piece& nextPiece = _state.piecePlaces.getPiece(nextPoint);

    if (nextPiece.isKing() && nextPiece.hasSameColor(prevPiece) && prevPiece.hasColor(_state.activeColor) && !nextPiece.hasSameColor(piece)) {
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

void Handler::_setPawnJumpMoves() {
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (piece.isPawn() && piece.hasColor(_state.activeColor) && _isPawnOnInitialRow(point, piece.isWhiteColor())) {
            int dy = piece.isWhiteColor() ? -1 : 1;
            Point stepPoint{point.x(), point.y() + dy};
            Point jumpPoint{point.x(), point.y() + dy * 2};
            if (_state.piecePlaces.contains(stepPoint) || _state.piecePlaces.contains(jumpPoint)) {
                continue;
            }
            _actionsPlaces.setAction(ActionType::PLACE, point, jumpPoint);
        }
    }
};

bool Handler::_isPawnOnPromotionRow(const Point& point, bool isWhiteColor) const {
    return isWhiteColor && point.y() == 0 || !isWhiteColor && point.y() == 7;
};

bool Handler::_isPawnOnInitialRow(const Point& point, bool isWhiteColor) const {
    return isWhiteColor && point.y() == 6 || !isWhiteColor && point.y() == 1;
};
