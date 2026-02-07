#include "handler.h"

void Handler::_removeEnPassantPieceIfNeeded(const Point& from, const Point& to) {
    const Piece& piece = _state.piecePlaces.getPiece(to);
    if (piece.isPawn() && to == _state.enPassant) {
        _state.piecePlaces.remove(Point{to.x(), from.y()});
    }
};

void Handler::_refreshEnPassantPoint(const Point& from, const Point& to) {
    const Piece& piece = _state.piecePlaces.getPiece(to);
    if (piece.isPawn() && _isPawnJumpMove(from, to, piece.isWhiteColor())) {
        _state.enPassant = from.next(piece.getPlaceDirections()[0]);
    } else {
        _state.enPassant = Point{};
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
            _actionsPlaces.setAction(Action::Type::PLACE, point, jumpPoint);
        }
    }
};

bool Handler::_isPawnOnInitialRow(const Point& point, bool isWhiteColor) const {
    return isWhiteColor && point.y() == 6 || !isWhiteColor && point.y() == 1;
};

bool Handler::_isPawnJumpMove(const Point& from, const Point& to, bool isWhiteColor) const {
    return isWhiteColor && from.y() == 6 && to.y() == 4 || !isWhiteColor && from.y() == 1 && to.y() == 3;
};
