#include "test_handler.h"

void testInitialPieces() {
    Handler handler{};

    int i = 0;
    for (Square* square : handler.getBoard().squares()) {
        if (square->point.y() > 1 && square->point.y() < 6) {
            assert(!handler.getState().piecePlaces.contains(square->point));
        } else {
            assert(handler.getState().piecePlaces.contains(square->point));
        }

        if (square->point.y() == 0 || square->point.y() == 7) {
            const Piece& piece = handler.getState().piecePlaces.at(square->point);
            assert(piece.isWhiteColor() == (square->point.y() == 7));
            if (square->point.x() == 0 || square->point.x() == 7) {
                assert(piece.getType() == PieceType::ROOK);
            } else if (square->point.x() == 1 || square->point.x() == 6) {
                assert(piece.getType() == PieceType::KNIGHT);
            } else if (square->point.x() == 2 || square->point.x() == 5) {
                assert(piece.getType() == PieceType::BISHOP);
            } else if (square->point.x() == 3) {
                assert(piece.getType() == PieceType::QUEEN);
            } else {
                assert(piece.getType() == PieceType::KING);
            }
        } else if (square->point.y() == 1 || square->point.y() == 6) {
            const Piece& piece = handler.getState().piecePlaces.at(square->point);
            assert(piece.isWhiteColor() == (square->point.y() == 6));
            assert(piece.getType() == PieceType::PAWN);
        }
        ++i;
    }
    assert(i == 64);
};
