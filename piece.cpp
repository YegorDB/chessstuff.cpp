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
            Direction{0, -1}
        }
    },
    {
        PieceColor::BLACK,
        {
            Direction{0, 1}
        }
    }
};

const std::unordered_map<PieceColor, std::vector<Direction>> Piece::PAWN_THREAT_DIRECTIONS{
    {
        PieceColor::WHITE,
        {
            Direction{-1, -1},
            Direction{1, -1}
        }
    },
    {
        PieceColor::BLACK,
        {
            Direction{-1, 1},
            Direction{1, 1}
        }
    }
};

Piece::Piece() {};

Piece::Piece(PieceType type, bool isWhiteColor) : _type(type){
    _color = isWhiteColor ? PieceColor::WHITE : PieceColor::BLACK;
};

void Piece::operator=(const Piece& other) {
    _type = other._type;
    _color = other._color;
};

const PieceType Piece::getType() const {
    return _type;
};

const PieceColor Piece::getColor() const {
    return _color;
};

const std::vector<Direction>& Piece::getPlaceDirections() const {
    if (_type == PieceType::PAWN) {
        return PAWN_PLACE_DIRECTIONS.at(_color);
    }
    return DIRECTIONS.at(_type);
};

const std::vector<Direction>& Piece::getThreatDirections() const {
    if (_type == PieceType::PAWN) {
        return PAWN_THREAT_DIRECTIONS.at(_color);
    }
    return DIRECTIONS.at(_type);
};

const std::string& Piece::getColorName() const {
    return COLOR_NAMES[isWhiteColor() ? 0 : 1];
};

bool Piece::isWhiteColor() const {
    return _color == PieceColor::WHITE;
};

bool Piece::hasColor(PieceColor color) const {
    return _color == color;
};

bool Piece::hasSameColor(const Piece& other) const {
    return _color == other._color;
};

bool Piece::isKing() const {
    return _type == PieceType::KING;
};
