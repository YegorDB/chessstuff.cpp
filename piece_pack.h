#pragma once

#include <array>
#include <unordered_map>

#include "piece.h"

using PiecePackPieces = std::unordered_map<PieceType, std::array<Piece, 8>>;

class PiecePack {
private:
    bool _isWhiteColor;
    PiecePackPieces _pieces;
    std::unordered_map<PieceType, int> _nextIndexes;

public:
    PiecePack(bool isWhiteColor);

    Piece* getPiece(PieceType pieceType);
    const PiecePackPieces getPieces() const;
};
