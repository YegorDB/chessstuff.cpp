#include "test_piece_pack.h"

void testPiecePack() {
    for (bool isWhiteColor : {true, false}) {
        PiecePack piecePack{isWhiteColor};

        Piece* king = piecePack.getPiece(PieceType::KING);
        assert(king->getType() == PieceType::KING);
        assert(king->isWhiteColor() == isWhiteColor);

        for (int i = 0; i < 8; ++i) {
            for (PieceType pieceType : {PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT, PieceType::PAWN}) {
                Piece* piece = piecePack.getPiece(pieceType);
                assert(piece->getType() == pieceType);
                assert(piece->isWhiteColor() == isWhiteColor);
            }
        }

        for (PieceType pieceType : {PieceType::KING, PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT, PieceType::PAWN}) {
            bool errorWasThrown = false;
            try {
                piecePack.getPiece(pieceType);
            } catch(std::runtime_error) {
                errorWasThrown = true;
            }
            assert(errorWasThrown);
        }

        PiecePackPieces pieces = piecePack.getPieces();
        std::unordered_map<PieceType, int> counter;
        for (PieceType pieceType : {PieceType::KING, PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT, PieceType::PAWN}) {
            for (Piece p : pieces.at(pieceType)) {
                if (p.getType() == pieceType) {
                    counter[pieceType]++;
                } else {
                    assert(p.getType() == PieceType::UNSET);
                }
            }
        }
        assert(counter.at(PieceType::KING) == 1);
        assert(counter.at(PieceType::QUEEN) == 8);
        assert(counter.at(PieceType::ROOK) == 8);
        assert(counter.at(PieceType::BISHOP) == 8);
        assert(counter.at(PieceType::KNIGHT) == 8);
        assert(counter.at(PieceType::PAWN) == 8);
    }

    std::cout << "testPiecePack OK" << std::endl;
};
