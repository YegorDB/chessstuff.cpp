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

    if (_rawStringParts.size() != 6) {
        throw std::runtime_error{"Wrong raw string parts count."};
    }
};

void FEN::_parseRawSringPiecesPlacesPart() {
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
    if (_rawStringParts[1].size() != 1 || !PIECE_COLOR_SYMBOLS.contains(_rawStringParts[1][0])) {
        throw std::runtime_error{"Wrong active color part."};
    }

    _state.activeColor = PIECE_COLOR_SYMBOLS.at(_rawStringParts[1][0]);
};

void FEN::_parseRawSringCastlesPart() {
    if (_rawStringParts[2] == "-") return;

    for (char c : _rawStringParts[2]) {
        if (c == 'K') {
            _state.castles.whiteKingSide = true;
        } else if (c == 'Q') {
            _state.castles.whiteQueenSide = true;
        } else if (c == 'k') {
            _state.castles.blackKingSide = true;
        } else if (c == 'q') {
            _state.castles.blackQueenSide = true;
        }
    }
};

void FEN::_parseRawSringEnPassantPart() {
    if (_rawStringParts[3] == "-") return;

    _state.enPassant = Square::nameToPoint(_rawStringParts[3]);
};

void FEN::_parseRawSringHalfmoveClockPart() {
    _state.halfmoveClock = _parseRawSringNumber(_rawStringParts[4]);
};

void FEN::_parseRawSringMovesCountPart() {
    _state.movesCount = _parseRawSringNumber(_rawStringParts[5]);
};

int FEN::_parseRawSringNumber(std::string number) {
    try {
        return std::stoi(number);
    } catch(std::invalid_argument) {
        throw std::runtime_error{"Invalid number argument."};
    } catch(std::out_of_range) {
        throw std::runtime_error{"Number argument out of range."};
    }
};

const std::string& FEN::getRawString() const {
    return _rawString;
};

const State& FEN::getState() const {
    return _state;
};
