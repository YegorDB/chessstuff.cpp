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

void ActionsPlaces::setAction(Action::Type type, const Point& byPoint, const Point& toPoint) {
    if (!byPoint.isValid() || !toPoint.isValid()) {
        throw std::runtime_error{"Wrong point."};
    }
    _items[byPoint].insert(type, Action::Relation::TO, toPoint);
    _items[toPoint].insert(type, Action::Relation::BY, byPoint);
};

void ActionsPlaces::clearActions() {
    for (auto& [point, actions] : _items) {
        actions.clear();
    }
};

void ActionsPlaces::erasePoints(const Point& byPoint, Action::Type type, const PointSet& toPoints) {
    for (const Point& toPoint : toPoints) {
        _items[byPoint].erase(type, Action::Relation::TO, toPoint);
        _items[toPoint].erase(type, Action::Relation::BY, byPoint);
    }
};
