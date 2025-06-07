#include "action.h"
#include "board.h"
#include "fen.h"

class Handler {
private:
    ActionsPlaces _actionsPlaces;
    Board _board;
    State _state;

    void _initPieces(const FEN& fen);
    void _clearActions();
    void _setActions();
    void _setBaseActions(std::vector<Square*>& bindedSquares);
    void _restrictKingActions();
    void _setAction(ActionType type, Square* bySquare, Square* toSquare);
    void _threatSquareAfterKingIfNeeded(Square* square, Square* prevSquare, Square* nextSquare);
    void _supportPieceAfterKingIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare);
    void _bindPieceIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare, std::vector<Square*>& bindedSquares);

public:
    Handler(const FEN& fen);
    Handler();

    const ActionsPlaces& getActionsPlaces();
    Board& getBoard();
    const State& getState();
};
