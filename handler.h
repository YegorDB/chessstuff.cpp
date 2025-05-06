#include "board.h"
#include "fen.h"

class Handler {
private:
    Board board;

    void initBoard();
    void initPieces();

    void clearActions();
    void setActions();
    void setAction(ActionType type, Square* bySquare, Square* toSquare);

public:
    Handler();

    Board& getBoard();
};
