#include "piece.h"

const std::vector<std::string> Piece::COLOR_NAMES{"white", "black"};

Piece::Piece(PieceType type, bool isWhiteColor) : type(type), isWhiteColor(isWhiteColor) {}

const std::vector<Direction>& Piece::getMoveDirections() const {
    return moveDirections;
}

const std::vector<Direction>& Piece::getAttackDirections() const {
    return getMoveDirections();
}

const std::string& Piece::getColorName() const {
    return COLOR_NAMES[isWhiteColor ? 0 : 1];
}

King::King(bool isWhiteColor) : Piece(PieceType::KING, isWhiteColor) {
    moveDirections = {
        Direction{-1, -1},
        Direction{0, -1},
        Direction{1, -1},
        Direction{-1, 0},
        Direction{1, 0},
        Direction{-1, 1},
        Direction{0, 1},
        Direction{1, 1}
    };
};

Queen::Queen(bool isWhiteColor) : Piece(PieceType::QUEEN, isWhiteColor) {
    moveDirections = {
        Direction{-1, -1, 7},
        Direction{0, -1, 7},
        Direction{1, -1, 7},
        Direction{-1, 0, 7},
        Direction{1, 0, 7},
        Direction{-1, 1, 7},
        Direction{0, 1, 7},
        Direction{1, 1, 7}
    };
};

Rook::Rook(bool isWhiteColor) : Piece(PieceType::ROOK, isWhiteColor) {
    moveDirections = {
        Direction{0, -1, 7},
        Direction{-1, 0, 7},
        Direction{1, 0, 7},
        Direction{0, 1, 7}
    };
};

Bishop::Bishop(bool isWhiteColor) : Piece(PieceType::BISHOP, isWhiteColor) {
    moveDirections = {
        Direction{-1, -1, 7},
        Direction{1, -1, 7},
        Direction{-1, 1, 7},
        Direction{1, 1, 7}
    };
};

Knight::Knight(bool isWhiteColor) : Piece(PieceType::KNIGHT, isWhiteColor) {
    moveDirections = {
        Direction{-1, -2},
        Direction{1, -2},
        Direction{-2, -1},
        Direction{2, -1},
        Direction{-2, 1},
        Direction{2, 1},
        Direction{-1, 2},
        Direction{1, 2}
    };
};

Pawn::Pawn(bool isWhiteColor) : Piece(PieceType::PAWN, isWhiteColor) {
    int step = isWhiteColor ? -1 : 1;
    moveDirections = {
        Direction{0, 1 * step}
    };
    firstMoveDirections = {
        Direction{0, 1 * step},
        Direction{0, 2 * step}
    };
    attackDirections = {
        Direction{-1, 1 * step},
        Direction{1, 1 * step}
    };
};

const std::vector<Direction>& Pawn::getFirstMoveDirections() const {
    return firstMoveDirections;
}

const std::vector<Direction>& Pawn::getAttackDirections() const {
    return attackDirections;
}
