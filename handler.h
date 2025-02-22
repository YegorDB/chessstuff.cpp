#include "board_item.h"

class Handler {
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
    Handler();

    BoardItems& getItems();
};
