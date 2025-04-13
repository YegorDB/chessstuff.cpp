#include "test_piece_pack.h"

void testPiecePack() {
    for (bool isWhiteColor : {true, false}) {
        PiecePack piecePack{isWhiteColor};

        assert(piecePack.king.type == PieceType::KING);
        assert(piecePack.king.isWhiteColor == isWhiteColor);

        assert(piecePack.queens.size() == 1);
        assert(piecePack.queens[0].type == PieceType::QUEEN);
        assert(piecePack.queens[0].isWhiteColor == isWhiteColor);

        assert(piecePack.rooks.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piecePack.rooks[i].type == PieceType::ROOK);
            assert(piecePack.rooks[i].isWhiteColor == isWhiteColor);
        }

        assert(piecePack.bishops.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piecePack.bishops[i].type == PieceType::BISHOP);
            assert(piecePack.bishops[i].isWhiteColor == isWhiteColor);
        }

        assert(piecePack.knights.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piecePack.knights[i].type == PieceType::KNIGHT);
            assert(piecePack.knights[i].isWhiteColor == isWhiteColor);
        }

        assert(piecePack.pawns.size() == 8);
        for (int i = 0; i < 8; ++i) {
            assert(piecePack.pawns[i].type == PieceType::PAWN);
            assert(piecePack.pawns[i].isWhiteColor == isWhiteColor);
        }
    }

    std::cout << "testPiecePack OK" << std::endl;
};
