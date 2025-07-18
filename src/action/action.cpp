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
