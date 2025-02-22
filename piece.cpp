#include "piece.h"

const std::vector<std::string> Piece::COLOR_NAMES{"white", "black"};

const std::unordered_map<PieceType, std::vector<Direction>> Piece::DIRECTIONS{
    {
        PieceType::KING,
        {
            Direction{-1, -1},
            Direction{0, -1},
            Direction{1, -1},
            Direction{-1, 0},
            Direction{1, 0},
            Direction{-1, 1},
            Direction{0, 1},
            Direction{1, 1}
        }
    },
    {
        PieceType::QUEEN,
        {
            Direction{-1, -1, 7},
            Direction{0, -1, 7},
            Direction{1, -1, 7},
            Direction{-1, 0, 7},
            Direction{1, 0, 7},
            Direction{-1, 1, 7},
            Direction{0, 1, 7},
            Direction{1, 1, 7}
        }
    },
    {
        PieceType::ROOK,
        {
            Direction{0, -1, 7},
            Direction{-1, 0, 7},
            Direction{1, 0, 7},
            Direction{0, 1, 7}
        }
    },
    {
        PieceType::BISHOP,
        {
            Direction{-1, -1, 7},
            Direction{1, -1, 7},
            Direction{-1, 1, 7},
            Direction{1, 1, 7}
        }
    },
    {
        PieceType::KNIGHT,
        {
            Direction{-1, -2},
            Direction{1, -2},
            Direction{-2, -1},
            Direction{2, -1},
            Direction{-2, 1},
            Direction{2, 1},
            Direction{-1, 2},
            Direction{1, 2}
        }
    }
};

const std::unordered_map<PieceColor, std::vector<Direction>> Piece::PAWN_PLACE_DIRECTIONS{
    {
        PieceColor::WHITE,
        {
            Direction{0, 1}
        }
    },
    {
        PieceColor::BLACK,
        {
            Direction{0, -1}
        }
    }
};

const std::unordered_map<PieceColor, std::vector<Direction>> Piece::PAWN_THREAT_DIRECTIONS{
    {
        PieceColor::WHITE,
        {
            Direction{-1, 1},
            Direction{1, 1}
        }
    },
    {
        PieceColor::BLACK,
        {
            Direction{-1, -1},
            Direction{1, -1}
        }
    }
};

Piece::Piece(PieceType type, bool isWhiteColor) : type(type), isWhiteColor(isWhiteColor) {}

const std::vector<Direction>& Piece::getPlaceDirections() const {
    if (type == PieceType::PAWN) {
        return PAWN_PLACE_DIRECTIONS.at(isWhiteColor ? PieceColor::WHITE : PieceColor::BLACK);
    }
    return DIRECTIONS.at(type);
}

const std::vector<Direction>& Piece::getThreatDirections() const {
    if (type == PieceType::PAWN) {
        return PAWN_THREAT_DIRECTIONS.at(isWhiteColor ? PieceColor::WHITE : PieceColor::BLACK);
    }
    return DIRECTIONS.at(type);
}

const std::string& Piece::getColorName() const {
    return COLOR_NAMES[isWhiteColor ? 0 : 1];
}

const bool Piece::hasSameColor(const Piece* other) const {
    return other != nullptr && isWhiteColor == other->isWhiteColor;
};

const bool Piece::isKing() const {
    return type == PieceType::KING;
};
