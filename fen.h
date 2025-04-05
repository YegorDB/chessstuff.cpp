#include <string>
#include <vector>
#include <unordered_map>

#include "state.h"

class FEN {
static const std::unordered_map<char, PieceInfo> PIECE_TYPE_SYMBOLS;
static const std::unordered_map<char, PieceColor> PIECE_COLOR_SYMBOLS;

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

public:
    FEN(std::string rawString);
    FEN(State state);
};
