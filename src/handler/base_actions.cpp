#include "handler.h"

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
                    if (piece.isPawn() && piece.hasColor(_state.activeColor) && *nextPoint == _state.enPassant) {
                        _actionsPlaces.setAction(ActionType::THREAT, point, *nextPoint);
                    }
                    prevPoint = *nextPoint;
                } else {
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
    }
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
        _actionsPlaces.setAction(ActionType::AFTER_KING_RESTRICTION, point, nextPoint);
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
        _actionsPlaces.setAction(ActionType::AFTER_KING_RESTRICTION, point, nextPoint);
    }
};
