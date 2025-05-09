#include "board.h"
#include "fen.h"

class Handler {
private:
    Board _board;
    State _state;

    void _initPieces();
    void _clearActions();
    void _setActions();
    void _setAction(ActionType type, Square* bySquare, Square* toSquare);

public:
    Handler();

    Board& getBoard();
    const State& getState();
};
