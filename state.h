#include "piece_places.h"

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
    Point enPassant = Point{8, 8};
    int halfmoveClock = 0;
    int movesCount = 0;
};
