#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "square.h"
#include "state.h"

class FEN {
private:
    static const std::unordered_map<char, PieceInfo> PIECE_TYPE_SYMBOLS_TO_PIECE_INFO;
    static const std::unordered_map<char, PieceColor> PIECE_COLOR_SYMBOLS_TO_PIECE_COLOR;
    static const std::unordered_map<PieceColor, std::unordered_map<PieceType, char>> PIECE_INFO_TO_PIECE_TYPE_SYMBOLS;
    static const std::unordered_map<PieceColor, char> PIECE_COLOR_TO_PIECE_COLOR_SYMBOLS;

    std::string _rawString;
    std::vector<std::string> _rawStringParts;
    State _state;

    void _splitRawString();
    void _parseRawSringPiecesPlacesPart();
    void _parseRawSringActiveColorPart();
    void _parseRawSringCastlesPart();
    void _parseRawSringEnPassantPart();
    void _parseRawSringHalfmoveClockPart();
    void _parseRawSringMovesCountPart();
    int _parseRawSringNumber(std::string number);

    void _stringifyPiecePlaces();
    void _stringifyAcivePieceColor();
    void _stringifyCastles();
    void _stringifyEnPassant();

public:
    static const std::string INITIAL_POSITION;

    FEN(std::string rawString);
    FEN(State state);

    const std::string& getRawString() const;
    const State& getState() const;
};
