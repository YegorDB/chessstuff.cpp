#pragma once

#include <unordered_map>

#include "../piece/piece.h"

struct State {
    struct CastleSides {
        bool kingSide = false;
        bool queenSide = false;
    };
    struct Result {
        enum class Type {
            UNSET = 0,
            DRAW = 1,
            CHECKMATE = 2
        };
        Type type = Type::UNSET;
        PieceColor winnerColor = PieceColor::UNSET;
    };
    using Castles = std::unordered_map<PieceColor, CastleSides>;

    PiecePlaces piecePlaces;
    PieceColor activeColor = PieceColor::WHITE;
    Castles castles = {
        {PieceColor::WHITE, CastleSides{}},
        {PieceColor::BLACK, CastleSides{}}
    };
    Point enPassant = Point{};
    int halfmoveClock = 0;
    int movesCount = 0;
    Point pawnPromotion = Point{};
    Result result = Result{};
};
