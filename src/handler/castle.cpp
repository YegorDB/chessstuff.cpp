#include "handler.h"

void Handler::_setCastleActions() {
    if (!_state.castles[_state.activeColor].kingSide && !_state.castles[_state.activeColor].queenSide) {
        return;
    }

    int firstRankY = _getFirstRankY();

    Point kingInitialPoint{4, firstRankY};
    const Piece king = _state.piecePlaces.getPiece(kingInitialPoint);    
    if (!king.isKing() || !king.hasColor(_state.activeColor) || king.getMovesCount() > 0) {
        throw std::runtime_error{"Wrong king piece to castle."};
    }

    if (!_actionsPlaces.getActions(kingInitialPoint).get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
        return;
    }

    if (_state.castles[_state.activeColor].kingSide) {
        _setCastleAction(true);
    }

    if (_state.castles[_state.activeColor].queenSide) {
        _setCastleAction(false);
    }
};

void Handler::_setCastleAction(bool isKingSide) {
    int firstRankY = _getFirstRankY();
    int rookInitialX = isKingSide ? 7 : 0;
    Point rookPoint{rookInitialX, firstRankY};

    const Piece rook = _state.piecePlaces.getPiece(rookPoint);
    if (!rook.isRook() || !rook.hasColor(_state.activeColor) || rook.getMovesCount() > 0) {
        throw std::runtime_error{"Wrong rook piece to castle."};
    }

    Point kingInitialPoint{4, firstRankY};

    bool isFreeWay = true;
    int stepCounter = 0;
    for (Point* point : Board::pointsByTwoPoints(kingInitialPoint, rookPoint)) {
        if (_state.piecePlaces.contains(*point)) {
            isFreeWay = false;
            break;
        }

        if (++stepCounter > 2) {
            continue;
        }

        Actions actions = _actionsPlaces.getActions(*point);
        if (!actions.get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
            isFreeWay = false;
            break;
        }
    }

    if (isFreeWay) {
        int kingCastleDx = isKingSide ? 2 : -2;
        int kingCasleX = kingInitialPoint.x() + kingCastleDx;
        Point kingCaslePoint{kingCasleX, firstRankY};
        _actionsPlaces.setAction(ActionType::PLACE, kingInitialPoint, kingCaslePoint);
    }
};

void Handler::_handleCastleAfterMove(const Point& from, const Point& to) {
    const Piece& piece = _state.piecePlaces.getPiece(to);

    if (piece.isKing()) {
        _handleCastleAfterKingMove(from, to);
    }

    if (piece.isRook()) {
        _handleCastleAfterRookMove(from, to);
    }
};

void Handler::_handleCastleAfterKingMove(const Point& from, const Point& to) {
    if (_state.castles[_state.activeColor].kingSide) {
        _handleCastleAfterKingMoveAdditionals(from, to, true);
        _state.castles[_state.activeColor].kingSide = false;
    }
    if (_state.castles[_state.activeColor].queenSide) {
        _handleCastleAfterKingMoveAdditionals(from, to, false);
        _state.castles[_state.activeColor].queenSide = false;
    }
};

void Handler::_handleCastleAfterRookMove(const Point& from, const Point& to) {
    bool isWhiteColor = _state.activeColor == PieceColor::WHITE;
    if (_isRookOnKingSideCastleSquare(from, isWhiteColor) && _state.castles[_state.activeColor].kingSide) {
        _state.castles[_state.activeColor].kingSide = false;
    }
    if (_isRookOnQueenSideCastleSquare(from, isWhiteColor) && _state.castles[_state.activeColor].queenSide) {
        _state.castles[_state.activeColor].queenSide = false;
    }
};

void Handler::_handleCastleAfterKingMoveAdditionals(const Point& from, const Point& to, bool isKingSide) {
    int firstRankY = _getFirstRankY();
    Point kingInitialPoint{4, firstRankY};
    int kingCastleX = isKingSide ? 6 : 2;
    Point kingCastlePoint{kingCastleX, firstRankY};

    if (from == kingInitialPoint && to == kingCastlePoint) {
        _castleRook(isKingSide);
        _currentHistoryMove.type = isKingSide ? HistoryMove::Type::KING_SIDE_CASTLE : HistoryMove::Type::QUEEN_SIDE_CASTLE;
    }
};

void Handler::_castleRook(bool isKingSide) {
    int firstRankY = _getFirstRankY();

    int rookInitialX = isKingSide ? 7 : 0;
    Point rookInitialPoint{rookInitialX, firstRankY};
    const Piece& rook = _state.piecePlaces.getPiece(rookInitialPoint);
    if (!rook.isRook()) {
        throw std::runtime_error{"Missed rook to castle."};
    }

    int rookCastleX = isKingSide ? 5 : 3;
    Point rookCastlePoint{rookCastleX, firstRankY};
    _state.piecePlaces.move(rookInitialPoint, rookCastlePoint);
};

int Handler::_getFirstRankY() const {
    return _state.activeColor == PieceColor::WHITE ? 7 : 0;
};

bool Handler::_isRookOnKingSideCastleSquare(const Point& point, bool isWhiteColor) const {
    return (
        point.x() == 7 &&
        (isWhiteColor && point.y() == 7 || !isWhiteColor && point.y() == 0)
    );
};

bool Handler::_isRookOnQueenSideCastleSquare(const Point& point, bool isWhiteColor) const {
    return (
        point.x() == 0 &&
        (isWhiteColor && point.y() == 7 || !isWhiteColor && point.y() == 0)
    );
};
