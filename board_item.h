#include "board_item_action.h"
#include "piece_pack.h"
#include "square.h"

class BoardItem {
public:
    Square square;
    Piece* piece = nullptr;
    BoardItemActions actions;

    BoardItem(Square square);
    BoardItem(Square square, Piece* piece);
};

using BoardItems = std::vector<std::vector<BoardItem>>;
