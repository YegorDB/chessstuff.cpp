#include "handler.h"

Handler::Response Handler::promotePawn(PieceType pieceType) {
    if (_state.pawnPromotion.isUndefined()) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION};
    } else if (!Piece::PAWN_PROMOTION_TYPES.contains(pieceType)) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION_PIECE_TYPE};
    }

    _currentHistoryMove.promotionType = pieceType;

    bool isWhiteColor = _state.activeColor == PieceColor::WHITE;
    Piece piece{pieceType, isWhiteColor};
    _state.piecePlaces.place(_state.pawnPromotion, piece);

    _state.pawnPromotion = Point{};
    bool resetHalfMoveClock = true;
    _endMove(resetHalfMoveClock);

    return Response{Response::Status::OK};
};

bool Handler::_setPromotionPawnIfNeeded(const Point& to) {
    const Piece& piece = _state.piecePlaces.getPiece(to);
    if (piece.isPawn() && _isPawnOnPromotionRow(to, piece.isWhiteColor())) {
        _state.pawnPromotion = to;
        _currentHistoryMove.type = HistoryMove::Type::PAWN_PROMOTION;
        return true;
    }
    return false;
};

bool Handler::_isPawnOnPromotionRow(const Point& point, bool isWhiteColor) const {
    return isWhiteColor && point.y() == 0 || !isWhiteColor && point.y() == 7;
};
