#include "board_item.h"

BoardItem::BoardItem(Square square) : square(square) {};

BoardItem::BoardItem(Square square, Piece* piece) : square(square), piece(piece) {};
