#include "moves_history.h"

const std::unordered_map<PieceType, std::string> Move::PIECE_TYPES_TO_SYMBOLS = {
    {PieceType::KING, "K"},
    {PieceType::QUEEN, "Q"},
    {PieceType::ROOK, "R"},
    {PieceType::BISHOP, "B"},
    {PieceType::KNIGHT, "N"},
    {PieceType::PAWN, ""},
};

Move::Move(
    PieceType pieceType,
    Point from,
    Point to,
    Type type,
    bool isAmbiguate,
    int checkersCount,
    bool isCheckMate,
    PieceType promotionType
) {
    pieceType = pieceType;
    from = from;
    to = to;
    type = type;
    isAmbiguate = isAmbiguate;
    checkersCount = checkersCount;
    isCheckMate = isCheckMate;
    promotionType = promotionType;
    _buidStringValue();
};

void Move::_buidStringValue() {
    if (type == Type::KING_SIDE_CASTLE) {
        _stringValue = "0-0";
    } else if (type == Type::QUEEN_SIDE_CASTLE) {
        _stringValue = "0-0-0";
    } else {
        _stringValue = PIECE_TYPES_TO_SYMBOLS.at(pieceType);

        if (isAmbiguate) {
            _stringValue += Square{from}.toString();
        }

        if (type == Type::TAKE) {
            _stringValue.push_back('x');
        }

        _stringValue += Square{to}.toString();

        if (type == Type::PAWN_PROMOTION) {
            _stringValue.push_back('=');
            _stringValue += PIECE_TYPES_TO_SYMBOLS.at(promotionType);
        }
    }

    if (isCheckMate) {
        _stringValue.push_back('#');
    } else if (checkersCount > 0) {
        for (int i = 0; i < checkersCount; i++) {
            _stringValue.push_back('+');
        }
    }
}

const std::string Move::toString() const {
    return _stringValue;
};
