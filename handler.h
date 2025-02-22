#include "board.h"
#include "piece_pack.h"

class Handler {
private:
    Board board;
    std::vector<PiecePack> piecePacks;

    void initBoard();
    void initPiecePacks();
    void initOneSidePieces(bool isWhiteColor);
    void initPieces();

    void clearActions();
    void setActions();
    void setAction(ActionType type, Square* bySquare, Square* toSquare);

public:
    Handler();

    Board& getBoard();
};
