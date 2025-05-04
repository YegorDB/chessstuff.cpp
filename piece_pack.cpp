#include <stdexcept>

#include "piece_pack.h"

PiecePack::PiecePack(bool isWhiteColor) : _isWhiteColor(isWhiteColor) {
    for (PieceType pieceType : {PieceType::KING, PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT, PieceType::PAWN}) {
        _pieces[pieceType] = {};
        _nextIndexes[pieceType] = 0;
    }
};

Piece* PiecePack::getPiece(PieceType pieceType) {
    if (pieceType == PieceType::KING && _nextIndexes[pieceType] > 0 || pieceType != PieceType::KING && _nextIndexes[pieceType] > 7) {
        throw std::runtime_error{"Max piece by type count reached."};
    }

    int nextIndex = _nextIndexes[pieceType]++;
    _pieces[pieceType][nextIndex] = Piece{pieceType, _isWhiteColor};
    return &(_pieces[pieceType][nextIndex]);
};

const PiecePackPieces PiecePack::getPieces() const {
    return _pieces;
};
