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
        enum class DrawType {
            UNSET = 0,
            STALEMATE = 1,
            INSUFFICIENT_MATERIAL = 2,
            THREEFOLD_REPETITION = 3,
            FIFTY_MOVE_RULE = 4
        };
        Type type = Type::UNSET;
        PieceColor winnerColor = PieceColor::UNSET;
        DrawType drawType = DrawType::UNSET;
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
    int movesCount = 1;
    Point pawnPromotion = Point{};
    Result result = Result{};
};
