#include "action.h"
#include "piece.h"
#include "square.h"

class BoardItem {
public:
    Square square;
    Piece* piece = nullptr;
    Actions actions;

    BoardItem(Square square);
    BoardItem(Square square, Piece* piece);

    static bool hasPiece(const BoardItem& item);
};
