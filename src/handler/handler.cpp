#include "handler.h"

Handler::Handler(const FEN& fen) {
    _initState(fen);
    _actionsPlaces.clearActions();
    _setActions();
    _validatePosition();
    _countPosition();
    _setResult();
};

Handler::Handler() : Handler(FEN{FEN::INITIAL_POSITION}) {};

void Handler::_initState(const FEN& fen) {
    _state = fen.getState();
};

const ActionsPlaces& Handler::getActionsPlaces() const {
    return _actionsPlaces;
};

const State& Handler::getState() const {
    return _state;
};

const HistoryMoves& Handler::getHistoryMoves() const {
    return _historyMoves;
};

const Handler::PositionCounts& Handler::getPositionCounts() const {
    return _positionCounts;
};

Handler::Response Handler::move(const Point& from, const Point& to) {
    if (_state.result.type != State::Result::Type::UNSET) {
        return Response{Response::Status::RESULT_REACHED};
    }

    const Piece& piece = _state.piecePlaces.getPiece(from);

    if (!from.isValid() || !to.isValid()) {
        return Response{Response::Status::INVALID_POINT};
    } else if (!_state.pawnPromotion.isUndefined()) {
        return Response{Response::Status::WRONG_PAWN_PROMOTION};
    } else if (piece.isUndefined()) {
        return Response{Response::Status::PIECE_DOES_NOT_EXIST};
    } else if (!piece.hasColor(_state.activeColor)) {
        return Response{Response::Status::WRONG_PIECE_COLOR};
    } else if (
        !_state.piecePlaces.contains(to) &&
        !_actionsPlaces.getActions(from).get(ActionType::PLACE).get(ActionRelation::TO).contains(to) &&
        !(
            piece.isPawn() &&
            to == _state.enPassant &&
            _actionsPlaces.getActions(from).get(ActionType::THREAT).get(ActionRelation::TO).contains(to)
        )
    ) {
        return Response{Response::Status::WRONG_DESTINATION};
    } else if (_state.piecePlaces.contains(to) && !_actionsPlaces.getActions(from).get(ActionType::THREAT).get(ActionRelation::TO).contains(to)) {
        return Response{Response::Status::WRONG_DESTINATION};
    }

    bool resetHalfMoveClock = piece.isPawn() || _state.piecePlaces.contains(to);

    _setCurrentHistoryMove(piece, from, to);
    _state.piecePlaces.move(from, to);
    _removeEnPassantPieceIfNeeded(from, to);
    _actionsPlaces.clearActions();
    _refreshEnPassantPoint(from, to);
    _handleCastleAfterMove(from, to);
    if (!_setPromotionPawnIfNeeded(to)) {
        _endMove(resetHalfMoveClock);
    }

    return Response{Response::Status::OK};
};

void Handler::_endMove(bool resetHalfMoveClock) {
    if (_state.activeColor == PieceColor::WHITE) {
        _state.activeColor = PieceColor::BLACK;
    } else if (_state.activeColor == PieceColor::BLACK) {
        _state.activeColor = PieceColor::WHITE;
        _state.movesCount++;
    }
    if (resetHalfMoveClock) {
        _state.halfmoveClock = 0;
    } else {
        ++_state.halfmoveClock;
    }
    _setActions();
    _countPosition();
    _setResult();
    _historyMoves.addMainLineMove(std::move(_currentHistoryMove));
};

void Handler::_setActions() {
    /*
    Active color piece has
    - squares without pieces to place to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to

    Inactive color piece has
    - squares without pieces to threat to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to
    */

    std::vector<Point> bindedPoints;
    _setBaseActions(bindedPoints);
    _setPawnJumpMoves();
    _setCastleActions();
    _restrictKingActions();
    _restrictBindedWithKingPiecesActions(bindedPoints);
    _restrictActionsOnKingCheck();
    // _validatePosition();
};
