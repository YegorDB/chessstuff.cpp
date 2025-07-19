#include "../action/action.h"
#include "../board/board.h"
#include "../fen/fen.h"

class Handler {
private:
    ActionsPlaces _actionsPlaces;
    State _state;

    void _initState(const FEN& fen);
    void _setActions();
    void _setBaseActions(std::vector<Point>& bindedPoints);
    void _restrictKingActions();
    void _threatSquareAfterKingIfNeeded(
        const Point& point,
        const Point& prevPoint,
        const Point& nextPoint
    );
    void _supportPieceAfterKingIfNeeded(
        const Point& point,
        const Point& prevPointWithPiece,
        const Point& nextPoint
    );
    void _bindPieceIfNeeded(
        const Point& point,
        const Point& prevPointWithPiece,
        const Point& nextPoint,
        std::vector<Point>& bindedPoints
    );

public:
    class Response {
    public:
        enum class Status {
            OK = 0,
            INVALID_POINT = 1,
            PIECE_DOES_NOT_EXIST = 2,
            WRONG_PIECE_COLOR = 3,
            WRONG_DESTINATION = 4,
        };

        const Status status;

        Response(Status status);

        bool isOk();
    };

    Handler(const FEN& fen);
    Handler();

    const ActionsPlaces& getActionsPlaces();
    const State& getState();
    Response move(const Point& from, const Point& to);
};
