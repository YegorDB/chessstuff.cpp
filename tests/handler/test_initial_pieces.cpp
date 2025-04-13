#include "test_handler.h"

void testInitialPieces() {
    Handler handler{};

    int i = 0;
    for (Square* square : handler.getBoard().squares()) {
        if (square->point.y() > 1 && square->point.y() < 6) {
            assert(square->getPiece() == nullptr);
        } else {
            assert(square->getPiece() != nullptr);
        }

        if (square->point.y() == 0 || square->point.y() == 7) {
            assert(!square->getPiece()->isWhiteColor == (square->point.y() == 7));
            if (square->point.x() == 0 || square->point.x() == 7) {
                assert(square->getPiece()->type == PieceType::ROOK);
            } else if (square->point.x() == 1 || square->point.x() == 6) {
                assert(square->getPiece()->type == PieceType::KNIGHT);
            } else if (square->point.x() == 2 || square->point.x() == 5) {
                assert(square->getPiece()->type == PieceType::BISHOP);
            } else if (square->point.x() == 3) {
                assert(square->getPiece()->type == PieceType::QUEEN);
            } else {
                assert(square->getPiece()->type == PieceType::KING);
            }
        } else if (square->point.y() == 1 || square->point.y() == 6) {
            assert(!square->getPiece()->isWhiteColor == (square->point.y() == 6));
            assert(square->getPiece()->type == PieceType::PAWN);
        }
        ++i;
    }
    assert(i == 64);
};
