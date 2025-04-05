#include <stdexcept>

#include "fen.h"

const std::unordered_map<char, PieceInfo> FEN::PIECE_TYPE_SYMBOLS{
    {'K', PieceInfo{PieceColor::WHITE, PieceType::KING}},
    {'Q', PieceInfo{PieceColor::WHITE, PieceType::QUEEN}},
    {'R', PieceInfo{PieceColor::WHITE, PieceType::ROOK}},
    {'B', PieceInfo{PieceColor::WHITE, PieceType::BISHOP}},
    {'N', PieceInfo{PieceColor::WHITE, PieceType::KNIGHT}},
    {'P', PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
    {'k', PieceInfo{PieceColor::BLACK, PieceType::KING}},
    {'q', PieceInfo{PieceColor::BLACK, PieceType::QUEEN}},
    {'r', PieceInfo{PieceColor::BLACK, PieceType::ROOK}},
    {'b', PieceInfo{PieceColor::BLACK, PieceType::BISHOP}},
    {'n', PieceInfo{PieceColor::BLACK, PieceType::KNIGHT}},
    {'p', PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
};

const std::unordered_map<char, PieceColor> FEN::PIECE_COLOR_SYMBOLS{
    {'w', PieceColor::WHITE},
    {'b', PieceColor::BLACK},
};

FEN::FEN(std::string rawString) : _rawString(rawString) {
    _splitRawString();
    _parseRawSringPiecesPlacesPart();
    _parseRawSringActiveColorPart();
    _parseRawSringCastlesPart();
    _parseRawSringEnPassantPart();
    _parseRawSringHalfmoveClockPart();
    _parseRawSringMovesCountPart();
};

FEN::FEN(State state) : _rawString(""), _state(state) {};

void FEN::_splitRawString() {
    _rawStringParts.clear();

    if (_rawString.empty()) {
        throw std::runtime_error{"Can't split empty string."}; 
    }

    std::string s;
    for (char c : _rawString) {
        if (c == ' ') {
            _rawStringParts.push_back(s);
            s.clear();
        } else {
            s.push_back(c);
        }
    }
    _rawStringParts.push_back(s);
};

void FEN::_parseRawSringPiecesPlacesPart() {
    if (_rawStringParts.empty()) {
        throw std::runtime_error{"Can't parse pieces plases part: there isn't first part."};
    }

    int x = 0, y = 0;
    for (char c : _rawStringParts[0]) {
        if (c == '/') {
            x = 0;
            y++;
        } else if (c > 48 && c <= 57) {
            x += c - 48;
        } else {
            if (!PIECE_TYPE_SYMBOLS.contains(c)) {
                throw std::runtime_error{"Wrong piece type symbol."};
            }
            _state.piecePlaces[Point(x, y)] = PIECE_TYPE_SYMBOLS.at(c);
            x++;
        }
    }
};

void FEN::_parseRawSringActiveColorPart() {
    if (_rawStringParts.size() < 2) {
        throw std::runtime_error{"Can't parse pieces plases part: there isn't second part."};
    }

    if (_rawStringParts[1].size() != 1 || !PIECE_COLOR_SYMBOLS.contains(_rawStringParts[1][0])) {
        throw std::runtime_error{"Wrong active color part."};
    }

    _state.activeColor = PIECE_COLOR_SYMBOLS.at(_rawStringParts[1][0]);
};

void FEN::_parseRawSringCastlesPart() {};

void FEN::_parseRawSringEnPassantPart() {};

void FEN::_parseRawSringHalfmoveClockPart() {};

void FEN::_parseRawSringMovesCountPart() {};
