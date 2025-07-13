#include <stdexcept>

#include "action.h"

Action::Action() {};

void Action::insert(ActionRelation relation, const Point& point) {
    _relations[relation].insert(point);
};

void Action::erase(ActionRelation relation, const Point& point) {
    _relations[relation].erase(point);
};

void Action::clear() {
    _relations[ActionRelation::TO].clear();
    _relations[ActionRelation::BY].clear();
};

const PointSet& Action::get(ActionRelation relation) const {
    return _relations.at(relation);
};

Actions::Actions() {};

void Actions::operator=(const Actions& other) {
    _inners = other._inners;
};

void Actions::insert(ActionType type, ActionRelation relation, const Point& point) {
    _inners[type].insert(relation, point);
};

void Actions::erase(ActionType type, ActionRelation relation, const Point& point) {
    _inners[type].erase(relation, point);
};

void Actions::clear() {
    _inners[ActionType::THREAT].clear();
    _inners[ActionType::SUPPORT].clear();
    _inners[ActionType::PLACE].clear();
    _inners[ActionType::XRAY].clear();
    _inners[ActionType::BIND].clear();
};

const Action& Actions::get(ActionType type) const {
    return _inners.at(type);
};

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
