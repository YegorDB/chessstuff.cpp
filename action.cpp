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
