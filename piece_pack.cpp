#include "piece_pack.h"

PiecePack::PiecePack(bool isWhiteColor) : king(Piece{PieceType::KING, isWhiteColor}) {
    queens.push_back(Piece{PieceType::QUEEN, isWhiteColor});
    for (int i = 0; i < 2; ++i) {
        rooks.push_back(Piece{PieceType::ROOK, isWhiteColor});
        bishops.push_back(Piece{PieceType::BISHOP, isWhiteColor});
        knights.push_back(Piece{PieceType::KNIGHT, isWhiteColor});
    }
    for (int i = 0; i < 8; ++i) {
        pawns.push_back(Piece{PieceType::PAWN, isWhiteColor});
    }
};
