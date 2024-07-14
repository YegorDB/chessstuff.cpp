#include "piece.h"

const std::vector<std::string> Piece::COLOR_NAMES{"white", "black"};

const std::unordered_map<PieceType, std::vector<Direction>> Piece::MOVE_DIRECTIONS{
    { PieceType::KING, {
        Direction{-1, -1},
        Direction{0, -1},
        Direction{1, -1},
        Direction{-1, 0},
        Direction{1, 0},
        Direction{-1, 1},
        Direction{0, 1},
        Direction{1, 1}
    }},
    { PieceType::QUEEN, {
        Direction{-1, -1, 7},
        Direction{0, -1, 7},
        Direction{1, -1, 7},
        Direction{-1, 0, 7},
        Direction{1, 0, 7},
        Direction{-1, 1, 7},
        Direction{0, 1, 7},
        Direction{1, 1, 7}
    }},
    { PieceType::ROOK, {
        Direction{0, -1, 7},
        Direction{-1, 0, 7},
        Direction{1, 0, 7},
        Direction{0, 1, 7},
    }},
    { PieceType::BISHOP, {
        Direction{-1, -1, 7},
        Direction{1, -1, 7},
        Direction{-1, 1, 7},
        Direction{1, 1, 7}
    }},
    { PieceType::KNIGHT, {
        Direction{-1, -2},
        Direction{1, -2},
        Direction{-2, -1},
        Direction{2, -1},
        Direction{-2, 1},
        Direction{2, 1},
        Direction{-1, 2},
        Direction{1, 2}
    }},
    { PieceType::PAWN, {
        Direction{0, -1},
    }},
};

Piece::Piece(PieceType type, bool isWhiteColor) : type(type), isWhiteColor(isWhiteColor) {
    color = isWhiteColor ? 0 : 1;
    colorName = COLOR_NAMES[color];
}

const std::vector<Direction>* Piece::getMoveDirections() const {
    auto kvPair = MOVE_DIRECTIONS.find(type);
    if (kvPair != MOVE_DIRECTIONS.end()) {
        return &(kvPair->second);
    }
    return nullptr;
}

const std::string& Piece::getColorName() const {
    return colorName;
}
