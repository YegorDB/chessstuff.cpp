#include "board_item.h"

// main data is matrix 8x8
// each item contains:
// - square
// - piece on square (or null)
// - piece to peace interactions (threat, support) direct and reverse [think about binds]
// - piece to square interactions (move, xray) direct and reverse
class Board {
private:
    BoardItems items;
    std::vector<PiecePack> piecePacks;

    void initItems();
    void initPiecePacks();
    void initOneSidePieces(bool isWhiteColor);
    void initPieces();

    void clearActions();
    void setActions();
    void setAction(ActionType type, BoardItem* byItem, BoardItem* toItem);

public:
    Board();

    BoardItems& getItems();
};
