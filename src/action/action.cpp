#include "action.h"

Action::Action() {};

void Action::insert(Action::Relation relation, const Point& point) {
    _relations[relation].insert(point);
};

void Action::erase(Action::Relation relation, const Point& point) {
    _relations[relation].erase(point);
};

void Action::clear() {
    _relations[Action::Relation::TO].clear();
    _relations[Action::Relation::BY].clear();
};

const PointSet& Action::get(Action::Relation relation) const {
    return _relations.at(relation);
};
