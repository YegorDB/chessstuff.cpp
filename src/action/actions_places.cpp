#include <stdexcept>

#include "action.h"

ActionsPlaces::ActionsPlaces() {
    for (Point* point : Board::points()) {
        _items[*point] = Actions{};
    }
}

const ActionsPlaces::Items& ActionsPlaces::getItems() const {
    return _items;
};

const Actions& ActionsPlaces::getActions(const Point& point) const {
    return _items.at(point);
};

void ActionsPlaces::setAction(ActionType type, const Point& byPoint, const Point& toPoint) {
    if (!byPoint.isValid() || !toPoint.isValid()) {
        throw std::runtime_error{"Wrong point."};
    }
    _items[byPoint].insert(type, ActionRelation::TO, toPoint);
    _items[toPoint].insert(type, ActionRelation::BY, byPoint);
};

void ActionsPlaces::clearActions() {
    for (auto& [point, actions] : _items) {
        actions.clear();
    }
};

void ActionsPlaces::erasePoints(
    const Point& point,
    ActionType type,
    ActionRelation relation,
    const PointSet& pointsToErase
) {
    for (const Point& pointToErase : pointsToErase) {
        _items[point].erase(type, relation, pointToErase);
    }
};
