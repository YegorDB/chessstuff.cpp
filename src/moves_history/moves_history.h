#pragma once

#include <string>
#include <unordered_map>

#include "../piece/piece.h"

class Move {
private:
    std::string _stringValue;

    void _buidStringValue();

public:
    static const std::unordered_map<PieceType, std::string> PIECE_TYPES_TO_SYMBOLS;

    enum class Type {
        PLACE = 0,
        TAKE = 1,
        PAWN_PROMOTION = 2,
        KING_SIDE_CASTLE = 3,
        QUEEN_SIDE_CASTLE = 4,
    };

    Move(
        PieceType pieceType,
        Point from,
        Point to,
        Type type,
        bool isAmbiguate,
        int checkersCount = 0,
        bool isCheckMate = false,
        PieceType promotionType = PieceType::UNSET
    );

    PieceType pieceType;
    Point from;
    Point to;
    Type type;
    bool isAmbiguate;
    int checkersCount;
    bool isCheckMate;
    PieceType promotionType;

    const std::string toString() const;
};
