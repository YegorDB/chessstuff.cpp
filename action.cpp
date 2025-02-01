#include "action.h"

Action::Action() {};

void Action::insert(ActionRelation relation, Square square) {
    _relations[relation].insert(square.point.hash());
};

void Action::clear() {
    _relations[ActionRelation::TO].clear();
    _relations[ActionRelation::BY].clear();
};

const ActionHashes& Action::get(ActionRelation relation) const {
    return _relations.at(relation);
};

Actions::Actions() {};

void Actions::insert(ActionType type, ActionRelation relation, Square square) {
    _inners[type].insert(relation, square);
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
