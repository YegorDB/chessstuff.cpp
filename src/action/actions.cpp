#include "action.h"

Actions::Actions() {};

void Actions::operator=(const Actions& other) {
    _inners = other._inners;
};

void Actions::insert(Action::Type type, Action::Relation relation, const Point& point) {
    _inners[type].insert(relation, point);
};

void Actions::erase(Action::Type type, Action::Relation relation, const Point& point) {
    _inners[type].erase(relation, point);
};

void Actions::clear() {
    _inners[Action::Type::THREAT].clear();
    _inners[Action::Type::SUPPORT].clear();
    _inners[Action::Type::PLACE].clear();
    _inners[Action::Type::XRAY].clear();
    _inners[Action::Type::BIND].clear();
};

const Action& Actions::get(Action::Type type) const {
    return _inners.at(type);
};
