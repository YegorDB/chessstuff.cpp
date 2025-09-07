#pragma once

#include <unordered_map>

#include "../piece/piece.h"

struct State {
    struct CastleSides {
        bool kingSide = false;
        bool queenSide = false;
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
};
