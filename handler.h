#include "action.h"
#include "board.h"
#include "fen.h"

class Handler {
private:
    ActionsPlaces _actionsPlaces;
    Board _board;
    State _state;

    void _initState(const FEN& fen);
    void _clearActions();
    void _setActions();
    void _setBaseActions(std::vector<Point>& bindedPoints);
    void _restrictKingActions();
    void _setAction(ActionType type, const Point& byPoint, const Point& toPoint);
    void _threatSquareAfterKingIfNeeded(const Point& point, const Point& prevPoint, const Point& nextPoint);
    void _supportPieceAfterKingIfNeeded(const Point& point, const Point& prevPointWithPiece, const Point& nextPoint);
    void _bindPieceIfNeeded(const Point& point, const Point& prevPointWithPiece, const Point& nextPoint, std::vector<Point>& bindedPoints);

public:
    Handler(const FEN& fen);
    Handler();

    const ActionsPlaces& getActionsPlaces();
    Board& getBoard();
    const State& getState();
};
