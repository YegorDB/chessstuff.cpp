#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "square.h"
#include "state.h"

class FEN {
private:
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
    int _parseRawSringNumber(const std::string& number);

    void _stringifyPiecePlaces();
    void _stringifyAcivePieceColor();
    void _stringifyCastles();
    void _stringifyEnPassant();

public:
    static const std::string INITIAL_POSITION;

    FEN(const std::string& rawString);
    FEN(const State& state);

    const std::string& getRawString() const;
    const State& getState() const;
};
