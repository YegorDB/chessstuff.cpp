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
    void _threatSquareAfterKingIfNeeded(Square* square, Square* prevSquare, Square* nextSquare);
    void _supportPieceAfterKingIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare);
    void _bindPieceIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare, std::vector<Square*>& bindedSquares);

public:
    Handler();

    Board& getBoard();
    const State& getState();
};
