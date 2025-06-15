#include <stdexcept>

#include "fen.h"

const std::string FEN::INITIAL_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

FEN::FEN(const std::string& rawString) : _rawString(rawString) {
    _splitRawString();
    _parseRawSringPiecesPlacesPart();
    _parseRawSringActiveColorPart();
    _parseRawSringCastlesPart();
    _parseRawSringEnPassantPart();
    _parseRawSringHalfmoveClockPart();
    _parseRawSringMovesCountPart();
};

FEN::FEN(const State& state) : _state(state) {
    _rawStringParts = {"", "", "", "", "", ""};

    _stringifyPiecePlaces();
    _stringifyAcivePieceColor();
    _stringifyCastles();
    _stringifyEnPassant();
    _rawStringParts[4] = std::to_string(_state.halfmoveClock);
    _rawStringParts[5] = std::to_string(_state.movesCount);

    _rawString = _rawStringParts[0];
    for (int i = 1; i < 6; ++i) {
        _rawString.push_back(' ');
        _rawString += _rawStringParts[i];
    }
};

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
            if (!Piece::SYMBOLS_TO_INFO.contains(c)) {
                throw std::runtime_error{"Wrong piece type symbol."};
            }
            auto [pieceType, pieceColor] = Piece::SYMBOLS_TO_INFO.at(c);
            bool isWhiteColor = pieceColor == PieceColor::WHITE;
            _state.piecePlaces[Point(x, y)] = Piece{pieceType, isWhiteColor};
            x++;
        }
    }
};

void FEN::_parseRawSringActiveColorPart() {
    if (_rawStringParts[1].size() != 1 || !Piece::SYMBOLS_TO_COLOR.contains(_rawStringParts[1][0])) {
        throw std::runtime_error{"Wrong active color part."};
    }

    _state.activeColor = Piece::SYMBOLS_TO_COLOR.at(_rawStringParts[1][0]);
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

int FEN::_parseRawSringNumber(const std::string& number) {
    try {
        return std::stoi(number);
    } catch(std::invalid_argument) {
        throw std::runtime_error{"Invalid number argument."};
    } catch(std::out_of_range) {
        throw std::runtime_error{"Number argument out of range."};
    }
};

void FEN::_stringifyPiecePlaces() {
    _rawStringParts[0] = "";
    for (int y = 0; y < 8; ++y) {
        int emptyCount = 0;

        for (int x = 0; x < 8; ++x) {
            Point point{x, y};
            if (!_state.piecePlaces.contains(point)) {
                ++emptyCount;
            } else {
                if (emptyCount > 0) {
                    _rawStringParts[0] += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                Piece piece = _state.piecePlaces.at(point);
                char symbol = Piece::INFO_TO_SYMBOLS.at(piece.getColor()).at(piece.getType());
                _rawStringParts[0].push_back(symbol);
            }
        }

        if (emptyCount > 0) {
            _rawStringParts[0] += std::to_string(emptyCount);
        }

        if (y < 7) {
            _rawStringParts[0].push_back('/');
        }
    }
};

void FEN::_stringifyAcivePieceColor() {
    _rawStringParts[1] = "";

    char pieceColorSymbol = Piece::COLOR_TO_SYMBOLS.at(_state.activeColor);
    _rawStringParts[1].push_back(pieceColorSymbol);
};

void FEN::_stringifyCastles() {
    _rawStringParts[2] = "";

    if (_state.castles.whiteKingSide) {
        _rawStringParts[2].push_back('K');
    }
    if (_state.castles.whiteQueenSide) {
        _rawStringParts[2].push_back('Q');
    }
    if (_state.castles.blackKingSide) {
        _rawStringParts[2].push_back('k');
    }
    if (_state.castles.blackQueenSide) {
        _rawStringParts[2].push_back('q');
    }
    if (_rawStringParts[2].empty()) {
        _rawStringParts[2].push_back('-');
    }
};

void FEN::_stringifyEnPassant() {
    _rawStringParts[3] = "";

    if (_state.enPassant.isUndefined() || !_state.enPassant.isValid()) {
        _rawStringParts[3].push_back('-');
    } else {
        Square square{_state.enPassant};
        _rawStringParts[3] = square.getName();
    }
};

const std::string& FEN::getRawString() const {
    return _rawString;
};

const State& FEN::getState() const {
    return _state;
};
