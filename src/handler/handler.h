#include <format>
#include <stdexcept>

#include "../action/action.h"
#include "../board/board.h"
#include "../fen/fen.h"
#include "../history/history.h"

class Handler {
public:
    using PositionCounts = std::unordered_map<std::string, int>;

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
            RESULT_REACHED = 7,
        };

        const Status status;

        Response(Status status);

        bool isOk();
    };

    Handler(const FEN& fen);
    Handler();

    const ActionsPlaces& getActionsPlaces() const;
    const State& getState() const;
    const HistoryMoves& getHistoryMoves() const;
    const PositionCounts& getPositionCounts() const;
    int getMaxPositionCount() const;
    Response move(const Point& from, const Point& to);
    Response promotePawn(PieceType pieceType);

private:
    ActionsPlaces _actionsPlaces;
    State _state;
    HistoryMoves _historyMoves;
    HistoryMove _currentHistoryMove;
    PositionCounts _positionCounts;
    int _maxPositionCount = 0;

    void _initState(const FEN& fen);
    void _endMove(bool resetHalfMoveClock);
    void _setActions();

    void _setBaseActions(std::vector<Point>& bindedPoints);
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

    void _restrictKingActions();
    void _restrictBindedWithKingPiecesActions(const std::vector<Point>& bindedPoints);
    void _restrictActionsOnKingCheck();
    void _eraseKingActions(Action::Type actionType, Action::Type restrictActionType, const Point& kingPoint);
    void _erasePieceActions(Action::Type actionType, const Point& piecePoint, const PointSet& awaliablePoints);

    bool _setPromotionPawnIfNeeded(const Point& to);
    bool _isPawnOnPromotionRow(const Point& point, bool isWhiteColor) const;

    void _removeEnPassantPieceIfNeeded(const Point& from, const Point& to);
    void _refreshEnPassantPoint(const Point& from, const Point& to);
    void _setPawnJumpMoves();
    bool _isPawnOnInitialRow(const Point& point, bool isWhiteColor) const;
    bool _isPawnJumpMove(const Point& from, const Point& to, bool isWhiteColor) const;

    void _setCastleActions();
    void _setCastleAction(bool isKingSide);
    void _handleCastleAfterMove(const Point& from, const Point& to);
    void _handleCastleAfterKingMove(const Point& from, const Point& to);
    void _handleCastleAfterRookMove(const Point& from, const Point& to);
    void _handleCastleAfterKingMoveAdditionals(const Point& from, const Point& to, bool isKingSide);
    void _castleRook(bool isKingSide);
    int _getFirstRankY() const;
    bool _isRookOnKingSideCastleSquare(const Point& point, bool isWhiteColor) const;
    bool _isRookOnQueenSideCastleSquare(const Point& point, bool isWhiteColor) const;

    void _validatePosition() const;
    void _validatePiecesCount() const;
    void _validatePawnsPositions() const;
    void _validateKingsThreats() const;
    bool _isPawnOnFirstRow(const Point& point, bool isWhiteColor) const;

    void _setResult();
    bool _checkIsCheckmate() const;
    bool _checkIsStalemate() const;
    bool _checkIsFiftyMoveRule() const;
    bool _checkIsInsufficientMaterial() const;
    bool _checkIsThreefoldRepetition() const;

    void _setCurrentHistoryMove(const Piece& piece, const Point& from, const Point& to);

    void _countPosition();
};
