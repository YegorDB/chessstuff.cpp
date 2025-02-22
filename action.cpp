#include "action.h"

Action::Action() {};

void Action::insert(ActionRelation relation, Point point) {
    _relations[relation].insert(point.hash());
};

void Action::clear() {
    _relations[ActionRelation::TO].clear();
    _relations[ActionRelation::BY].clear();
};

const ActionHashes& Action::get(ActionRelation relation) const {
    return _relations.at(relation);
};

Actions::Actions() {};

void Actions::insert(ActionType type, ActionRelation relation, Point point) {
    _inners[type].insert(relation, point);
};

void Actions::clear() {
    _inners[ActionType::THREAT].clear();
    _inners[ActionType::SUPPORT].clear();
    _inners[ActionType::PLACE].clear();
    _inners[ActionType::XRAY].clear();
};

const Action& Actions::get(ActionType type) const {
    return _inners.at(type);
};
