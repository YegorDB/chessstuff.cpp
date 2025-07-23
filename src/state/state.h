#pragma once

#include "../piece/piece.h"

struct State {
    struct Castles {
        bool whiteKingSide = false;
        bool whiteQueenSide = false;
        bool blackKingSide = false;
        bool blackQueenSide = false;
    };

    PiecePlaces piecePlaces;
    PieceColor activeColor = PieceColor::WHITE;
    Castles castles;
    Point enPassant = Point{};
    int halfmoveClock = 0;
    int movesCount = 0;
    Point pawnPromotion = Point{};
};
