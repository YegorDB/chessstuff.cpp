#include "piece.h"

const std::vector<std::string> Piece::COLOR_NAMES{"white", "black"};

const std::unordered_map<Piece::Color, std::unordered_map<Piece::Type, std::string>> Piece::VISIBLE_SYMBOLS {
    {
        Piece::Color::WHITE, {
            {Piece::Type::KING, "\u2654"},
            {Piece::Type::QUEEN, "\u2655"},
            {Piece::Type::ROOK, "\u2656"},
            {Piece::Type::BISHOP, "\u2657"},
            {Piece::Type::KNIGHT, "\u2658"},
            {Piece::Type::PAWN, "\u2659"},
        }
    },
    {
        Piece::Color::BLACK, {
            {Piece::Type::KING, "\u265A"},
            {Piece::Type::QUEEN, "\u265B"},
            {Piece::Type::ROOK, "\u265C"},
            {Piece::Type::BISHOP, "\u265D"},
            {Piece::Type::KNIGHT, "\u265E"},
            {Piece::Type::PAWN, "\u265F"},
        }
    }
};

const std::unordered_map<char, std::pair<Piece::Type, Piece::Color>> Piece::SYMBOLS_TO_INFO{
    {'K', {Piece::Type::KING, Piece::Color::WHITE}},
    {'Q', {Piece::Type::QUEEN, Piece::Color::WHITE}},
    {'R', {Piece::Type::ROOK, Piece::Color::WHITE}},
    {'B', {Piece::Type::BISHOP, Piece::Color::WHITE}},
    {'N', {Piece::Type::KNIGHT, Piece::Color::WHITE}},
    {'P', {Piece::Type::PAWN, Piece::Color::WHITE}},
    {'k', {Piece::Type::KING, Piece::Color::BLACK}},
    {'q', {Piece::Type::QUEEN, Piece::Color::BLACK}},
    {'r', {Piece::Type::ROOK, Piece::Color::BLACK}},
    {'b', {Piece::Type::BISHOP, Piece::Color::BLACK}},
    {'n', {Piece::Type::KNIGHT, Piece::Color::BLACK}},
    {'p', {Piece::Type::PAWN, Piece::Color::BLACK}},
};

const std::unordered_map<char, Piece::Color> Piece::SYMBOLS_TO_COLOR{
    {'w', Piece::Color::WHITE},
    {'b', Piece::Color::BLACK},
};

const std::unordered_map<Piece::Color, std::unordered_map<Piece::Type, char>> Piece::INFO_TO_SYMBOLS{
    {
        Piece::Color::WHITE,
        {
            {Piece::Type::KING, 'K'},
            {Piece::Type::QUEEN, 'Q'},
            {Piece::Type::ROOK, 'R'},
            {Piece::Type::BISHOP, 'B'},
            {Piece::Type::KNIGHT, 'N'},
            {Piece::Type::PAWN, 'P'},
        }
    },
    {
        Piece::Color::BLACK,
        {
            {Piece::Type::KING, 'k'},
            {Piece::Type::QUEEN, 'q'},
            {Piece::Type::ROOK, 'r'},
            {Piece::Type::BISHOP, 'b'},
            {Piece::Type::KNIGHT, 'n'},
            {Piece::Type::PAWN, 'p'},
        }
    },
};

const std::unordered_map<Piece::Color, char> Piece::COLOR_TO_SYMBOLS{
    {Piece::Color::WHITE, 'w'},
    {Piece::Color::BLACK, 'b'},
};

const std::unordered_set<Piece::Type> Piece::PAWN_PROMOTION_TYPES{
    Piece::Type::QUEEN,
    Piece::Type::ROOK,
    Piece::Type::BISHOP,
    Piece::Type::KNIGHT
};

const std::unordered_map<Piece::Type, std::vector<Direction>> Piece::DIRECTIONS{
    {
        Piece::Type::KING,
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
        Piece::Type::QUEEN,
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
        Piece::Type::ROOK,
        {
            Direction{0, -1, 7},
            Direction{-1, 0, 7},
            Direction{1, 0, 7},
            Direction{0, 1, 7}
        }
    },
    {
        Piece::Type::BISHOP,
        {
            Direction{-1, -1, 7},
            Direction{1, -1, 7},
            Direction{-1, 1, 7},
            Direction{1, 1, 7}
        }
    },
    {
        Piece::Type::KNIGHT,
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

const std::unordered_map<Piece::Color, std::vector<Direction>> Piece::PAWN_PLACE_DIRECTIONS{
    {
        Piece::Color::WHITE,
        {
            Direction{0, -1}
        }
    },
    {
        Piece::Color::BLACK,
        {
            Direction{0, 1}
        }
    }
};

const std::unordered_map<Piece::Color, std::vector<Direction>> Piece::PAWN_THREAT_DIRECTIONS{
    {
        Piece::Color::WHITE,
        {
            Direction{-1, -1},
            Direction{1, -1}
        }
    },
    {
        Piece::Color::BLACK,
        {
            Direction{-1, 1},
            Direction{1, 1}
        }
    }
};

Piece::Piece() {};

Piece::Piece(Piece::Type type, bool isWhiteColor) : _type(type){
    _color = isWhiteColor ? Piece::Color::WHITE : Piece::Color::BLACK;
};

void Piece::operator=(const Piece& other) {
    _type = other._type;
    _color = other._color;
    _movesCount = other._movesCount;
};

bool Piece::operator==(const Piece& other) const {
    return (_type == other._type && _color == other._color);
};

void Piece::increaseMovesCount() {
    _movesCount++;
};

const Piece::Type Piece::getType() const {
    return _type;
};

const Piece::Color Piece::getColor() const {
    return _color;
};

const std::vector<Direction>& Piece::getPlaceDirections() const {
    if (_color == Piece::Color::UNSET || _type == Piece::Type::UNSET) {
        throw std::runtime_error{"There is no place directions to unset piece."};
    }
    if (_type == Piece::Type::PAWN) {
        return PAWN_PLACE_DIRECTIONS.at(_color);
    }
    return DIRECTIONS.at(_type);
};

const std::vector<Direction>& Piece::getThreatDirections() const {
    if (_color == Piece::Color::UNSET || _type == Piece::Type::UNSET) {
        throw std::runtime_error{"There is no threat directions to unset piece."};
    }
    if (_type == Piece::Type::PAWN) {
        return PAWN_THREAT_DIRECTIONS.at(_color);
    }
    return DIRECTIONS.at(_type);
};

const std::string& Piece::getColorName() const {
    if (_color == Piece::Color::UNSET || _type == Piece::Type::UNSET) {
        throw std::runtime_error{"There is no color name to unset piece."};
    }
    return COLOR_NAMES[isWhiteColor() ? 0 : 1];
};

const std::string& Piece::getVisibleSymbol() const {
    if (_color == Piece::Color::UNSET || _type == Piece::Type::UNSET) {
        throw std::runtime_error{"There is no visible symbol to unset piece."};
    }
    return VISIBLE_SYMBOLS.at(_color).at(_type);
};

int Piece::getMovesCount() const {
    return _movesCount;
};

bool Piece::isWhiteColor() const {
    return _color == Piece::Color::WHITE;
};

bool Piece::hasColor(Piece::Color color) const {
    return _color == color;
};

bool Piece::hasSameColor(const Piece& other) const {
    return _color == other._color;
};

bool Piece::hasSameType(const Piece& other) const {
    return _type == other._type;
};

bool Piece::isKing() const {
    return _type == Piece::Type::KING;
};

bool Piece::isQueen() const {
    return _type == Piece::Type::QUEEN;
};

bool Piece::isRook() const {
    return _type == Piece::Type::ROOK;
};

bool Piece::isBishop() const {
    return _type == Piece::Type::BISHOP;
};

bool Piece::isKnight() const {
    return _type == Piece::Type::KNIGHT;
};

bool Piece::isPawn() const {
    return _type == Piece::Type::PAWN;
};

bool Piece::isUndefined() const {
    return _type == Piece::Type::UNSET || _color == Piece::Color::UNSET;
};
