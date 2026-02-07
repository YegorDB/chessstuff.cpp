#include "handler.h"

void Handler::_setCurrentHistoryMove(const Piece& piece, const Point& from, const Point& to) {
    Action::Type actionType = _state.piecePlaces.contains(to) ? Action::Type::THREAT : Action::Type::PLACE;
    HistoryMove::Type historyMoveType = _state.piecePlaces.contains(to) ? HistoryMove::Type::TAKE : HistoryMove::Type::PLACE;

    _currentHistoryMove = HistoryMove(piece.getType(), from, to, historyMoveType, 0, false, PieceType::UNSET, PointSet{});

    for (Point p : _actionsPlaces.getActions(to).get(actionType).get(Action::Relation::BY)) {
        if (p != from && _state.piecePlaces.getPiece(p).hasSameType(piece)) {
            _currentHistoryMove.otherCandidates.insert(p);
        }
    }
};
