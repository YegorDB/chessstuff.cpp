#include <stdexcept>

#include "piece.h"

const std::vector<std::string> Piece::COLOR_NAMES{"white", "black"};

const std::unordered_map<PieceColor, std::unordered_map<PieceType, std::string>> Piece::VISIBLE_SYMBOLS {
    {
        PieceColor::WHITE, {
            {PieceType::KING, "\u2654"},
            {PieceType::QUEEN, "\u2655"},
            {PieceType::ROOK, "\u2656"},
            {PieceType::BISHOP, "\u2657"},
            {PieceType::KNIGHT, "\u2658"},
            {PieceType::PAWN, "\u2659"},
        }
    },
    {
        PieceColor::BLACK, {
            {PieceType::KING, "\u265A"},
            {PieceType::QUEEN, "\u265B"},
            {PieceType::ROOK, "\u265C"},
            {PieceType::BISHOP, "\u265D"},
            {PieceType::KNIGHT, "\u265E"},
            {PieceType::PAWN, "\u265F"},
        }
    }
};

const std::unordered_map<char, std::pair<PieceType, PieceColor>> Piece::SYMBOLS_TO_INFO{
    {'K', {PieceType::KING, PieceColor::WHITE}},
    {'Q', {PieceType::QUEEN, PieceColor::WHITE}},
    {'R', {PieceType::ROOK, PieceColor::WHITE}},
    {'B', {PieceType::BISHOP, PieceColor::WHITE}},
    {'N', {PieceType::KNIGHT, PieceColor::WHITE}},
    {'P', {PieceType::PAWN, PieceColor::WHITE}},
    {'k', {PieceType::KING, PieceColor::BLACK}},
    {'q', {PieceType::QUEEN, PieceColor::BLACK}},
    {'r', {PieceType::ROOK, PieceColor::BLACK}},
    {'b', {PieceType::BISHOP, PieceColor::BLACK}},
    {'n', {PieceType::KNIGHT, PieceColor::BLACK}},
    {'p', {PieceType::PAWN, PieceColor::BLACK}},
};

const std::unordered_map<char, PieceColor> Piece::SYMBOLS_TO_COLOR{
    {'w', PieceColor::WHITE},
    {'b', PieceColor::BLACK},
};

const std::unordered_map<PieceColor, std::unordered_map<PieceType, char>> Piece::INFO_TO_SYMBOLS{
    {
        PieceColor::WHITE,
        {
            {PieceType::KING, 'K'},
            {PieceType::QUEEN, 'Q'},
            {PieceType::ROOK, 'R'},
            {PieceType::BISHOP, 'B'},
            {PieceType::KNIGHT, 'N'},
            {PieceType::PAWN, 'P'},
        }
    },
    {
        PieceColor::BLACK,
        {
            {PieceType::KING, 'k'},
            {PieceType::QUEEN, 'q'},
            {PieceType::ROOK, 'r'},
            {PieceType::BISHOP, 'b'},
            {PieceType::KNIGHT, 'n'},
            {PieceType::PAWN, 'p'},
        }
    },
};

const std::unordered_map<PieceColor, char> Piece::COLOR_TO_SYMBOLS{
    {PieceColor::WHITE, 'w'},
    {PieceColor::BLACK, 'b'},
};

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

const std::string& Piece::getVisibleSymbol() const {
    if (_color == PieceColor::UNSET || _type == PieceType::UNSET) {
        throw std::runtime_error{"There is no visible symbol to unset piece."};
    }
    return VISIBLE_SYMBOLS.at(_color).at(_type);
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
