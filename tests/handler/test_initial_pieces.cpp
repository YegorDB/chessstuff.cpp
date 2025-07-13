#include "test_handler.h"

void testInitialPieces() {
    Handler handler{};

    int i = 0;
    for (Point* p : Board::points()) {
        Point point = *p;
        if (point.y() > 1 && point.y() < 6) {
            assert(!handler.getState().piecePlaces.contains(point));
        } else {
            assert(handler.getState().piecePlaces.contains(point));
        }

        if (point.y() == 0 || point.y() == 7) {
            const Piece& piece = handler.getState().piecePlaces.at(point);
            assert(piece.isWhiteColor() == (point.y() == 7));
            if (point.x() == 0 || point.x() == 7) {
                assert(piece.getType() == PieceType::ROOK);
            } else if (point.x() == 1 || point.x() == 6) {
                assert(piece.getType() == PieceType::KNIGHT);
            } else if (point.x() == 2 || point.x() == 5) {
                assert(piece.getType() == PieceType::BISHOP);
            } else if (point.x() == 3) {
                assert(piece.getType() == PieceType::QUEEN);
            } else {
                assert(piece.getType() == PieceType::KING);
            }
        } else if (point.y() == 1 || point.y() == 6) {
            const Piece& piece = handler.getState().piecePlaces.at(point);
            assert(piece.isWhiteColor() == (point.y() == 6));
            assert(piece.getType() == PieceType::PAWN);
        }
        ++i;
    }
    assert(i == 64);
};
