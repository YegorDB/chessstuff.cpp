#include "handler.h"

void Handler::_restrictKingActions() {
    const Point& kingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    _eraseKingActions(Action::Type::PLACE, Action::Type::THREAT, kingPoint);
    _eraseKingActions(Action::Type::THREAT, Action::Type::SUPPORT, kingPoint);
    _eraseKingActions(Action::Type::PLACE, Action::Type::AFTER_KING_RESTRICTION, kingPoint);
    _eraseKingActions(Action::Type::THREAT, Action::Type::AFTER_KING_RESTRICTION, kingPoint);
};

void Handler::_restrictBindedWithKingPiecesActions(const std::vector<Point>& bindedPoints) {
    const Point& kingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    for (const Point& point : bindedPoints) {
        const PointSet& bindByPoints = _actionsPlaces.getActions(point).get(Action::Type::BIND).get(Action::Relation::BY);
        if (bindByPoints.size() != 1) {
            throw std::runtime_error{"Wrong bind by points set size."};
        }
        const Point& bindByPoint = *(bindByPoints.begin());

        PointSet awaliablePoints;
        for (Point* p : Board::pointsByTwoPoints(kingPoint, bindByPoint, false, true)) {
            awaliablePoints.insert(Point{p->x(), p->y()});
        }

        for (Action::Type actionType : {Action::Type::PLACE, Action::Type::THREAT}) {
            _erasePieceActions(actionType, point, awaliablePoints);
        }
    }
};

void Handler::_restrictActionsOnKingCheck() {
    const Point& kingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    const PointSet& kingCheckers = _actionsPlaces.getActions(kingPoint).get(Action::Type::THREAT).get(Action::Relation::BY);

    _currentHistoryMove.checkersCount = kingCheckers.size();

    if (kingCheckers.empty()) {
        return;
    }

    PointSet awaliablePoints;
    if (kingCheckers.size() == 1) {
        const Point& checkerPoint = *(kingCheckers.begin());
        const Piece& checker = _state.piecePlaces.getPiece(checkerPoint);
        if (checker.isKnight() || checker.isPawn()) {
            awaliablePoints.insert(checkerPoint);
        } else {
            for (Point* p : Board::pointsByTwoPoints(kingPoint, checkerPoint, false, true)) {
                awaliablePoints.insert(Point{p->x(), p->y()});
            }
        }
    }

    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (!piece.hasColor(_state.activeColor) || piece.isKing()) {
            continue;
        }

        for (Action::Type actionType : {Action::Type::PLACE, Action::Type::THREAT}) {
            _erasePieceActions(actionType, point, awaliablePoints);
        }
    }
};

void Handler::_eraseKingActions(Action::Type actionType, Action::Type restrictActionType, const Point& kingPoint) {
    PointSet pointsToErase;
    for (const Point& p : _actionsPlaces.getActions(kingPoint).get(actionType).get(Action::Relation::TO)) {
        const Actions& nextSquareActions = _actionsPlaces.getActions(p);
        if (!nextSquareActions.get(restrictActionType).get(Action::Relation::BY).empty()) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(kingPoint, actionType, pointsToErase);
}

void Handler::_erasePieceActions(Action::Type actionType, const Point& piecePoint, const PointSet& awaliablePoints) {
    PointSet pointsToErase;
    for (const Point& p : _actionsPlaces.getActions(piecePoint).get(actionType).get(Action::Relation::TO)) {
        if (!awaliablePoints.contains(p)) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(piecePoint, actionType, pointsToErase);
};
