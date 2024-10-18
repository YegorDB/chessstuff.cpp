#include "piece_pack.h"

PiecePack::PiecePack(bool isWhiteColor) : king(PieceItem{King(isWhiteColor)}) {
    queens.push_back(PieceItem{Queen(isWhiteColor)});
    for (int i = 0; i < 2; ++i) {
        rooks.push_back(PieceItem{Rook(isWhiteColor)});
        bishops.push_back(PieceItem{Bishop(isWhiteColor)});
        knights.push_back(PieceItem{Knight(isWhiteColor)});
    }
    for (int i = 0; i < 8; ++i) {
        pawns.push_back(PieceItem{Pawn(isWhiteColor)});
    }
};
