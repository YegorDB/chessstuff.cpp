#include "handler.h"

void Handler::_restrictKingActions(const Point& kingPoint) {
    const Actions& kingActions = _actionsPlaces.getActions(kingPoint);

    _eraseKingActions(ActionType::PLACE, ActionType::THREAT, kingPoint, kingActions);
    _eraseKingActions(ActionType::THREAT, ActionType::SUPPORT, kingPoint, kingActions);
};

void Handler::_eraseKingActions(
    ActionType actionType,
    ActionType restrictActionType,
    const Point& kingPoint,
    const Actions& kingActions
) {
    PointSet pointsToErase;
    for (const Point& p : kingActions.get(actionType).get(ActionRelation::TO)) {
        const Actions& nextSquareActions = _actionsPlaces.getActions(p);
        if (!nextSquareActions.get(restrictActionType).get(ActionRelation::BY).empty()) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(kingPoint, actionType, ActionRelation::TO, pointsToErase);
}

void Handler::_restrictBindedWithKingPiecesActions(const Point& kingPoint, const std::vector<Point>& bindedPoints) {
    for (const Point& point : bindedPoints) {
        const Actions& pieceActions = _actionsPlaces.getActions(point);

        const PointSet& bindByPoints = pieceActions.get(ActionType::BIND).get(ActionRelation::BY);
        if (bindByPoints.size() != 1) {
            throw std::runtime_error{"Wrong bind by points set size."};
        }
        const Point& bindByPoint = *(bindByPoints.begin());

        PointSet awaliablePoints;
        for (Point* p : Board::pointsByTwoPoints(kingPoint, bindByPoint, false, true)) {
            awaliablePoints.insert(Point{p->x(), p->y()});
        }

        _eraseBindedWithKingPiecesActions(ActionType::PLACE, point, pieceActions, awaliablePoints);
        _eraseBindedWithKingPiecesActions(ActionType::THREAT, point, pieceActions, awaliablePoints);
    }
};

void Handler::_eraseBindedWithKingPiecesActions(
    ActionType actionType,
    const Point& point,
    const Actions& pieceActions,
    const PointSet& awaliablePoints
) {
    PointSet pointsToErase;
    for (const Point& p : pieceActions.get(actionType).get(ActionRelation::TO)) {
        if (!awaliablePoints.contains(p)) {
            pointsToErase.insert(p);
        }
    }
    _actionsPlaces.erasePoints(point, actionType, ActionRelation::TO, pointsToErase);
};
