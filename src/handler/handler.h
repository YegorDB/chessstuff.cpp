#include <stdexcept>

#include "../action/action.h"
#include "../board/board.h"
#include "../fen/fen.h"

class Handler {
public:
    class Response {
    public:
        enum class Status {
            OK = 0,
            INVALID_POINT = 1,
            PIECE_DOES_NOT_EXIST = 2,
            WRONG_PIECE_COLOR = 3,
            WRONG_DESTINATION = 4,
            WRONG_PAWN_PROMOTION = 5,
            WRONG_PAWN_PROMOTION_PIECE_TYPE = 6,
        };

        const Status status;

        Response(Status status);

        bool isOk();
    };

    class CastlePart {
    private:
        ActionsPlaces& _actionsPlaces;
        State& _state;

        void _setAction(bool isKingSide);
        void _afterKingMove(const Point& from, const Point& to);
        void _afterRookMove(const Point& from, const Point& to);
        void _afterKingMoveAdditionals(const Point& from, const Point& to, bool isKingSide);
        void _moveRook(bool isKingSide);

        int _getFirstRankY() const;
        bool _isRookOnKingSideCastleSquare(const Point& point, bool isWhiteColor) const;
        bool _isRookOnQueenSideCastleSquare(const Point& point, bool isWhiteColor) const;

    public:
        CastlePart(State& state, ActionsPlaces& actionsPlaces);

        void setActions();
        void afterMove(const Point& from, const Point& to);
    };

    Handler(const FEN& fen);
    Handler();

    const ActionsPlaces& getActionsPlaces();
    const State& getState();
    Response move(const Point& from, const Point& to);
    Response promotePawn(PieceType pieceType);

private:
    ActionsPlaces _actionsPlaces;
    State _state;
    CastlePart _castlePart;

    void _initState(const FEN& fen);
    void _endMove();
    void _setActions();
    void _setBaseActions(std::vector<Point>& bindedPoints);
    const Point& _getActiveKingPoint() const;
    void _restrictKingActions(const Point& kingPoint);
    void _eraseKingActions(
        ActionType actionType,
        ActionType restrictActionType,
        const Point& kingPoint,
        const Actions& kingActions
    );
    void _restrictBindedWithKingPiecesActions(const Point& kingPoint, const std::vector<Point>& bindedPoints);
    void _eraseBindedWithKingPiecesActions(
        ActionType actionType,
        const Point& point,
        const Actions& pieceActions,
        const PointSet& awaliablePoints
    );
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
    void _setPawnJumpMoves();

    bool _isPawnOnPromotionRow(const Point& point, bool isWhiteColor) const;
    bool _isPawnOnInitialRow(const Point& point, bool isWhiteColor) const;
    bool _isPawnJumpMove(const Point& from, const Point& to, bool isWhiteColor) const;
};
