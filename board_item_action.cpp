#include "board_item_action.h"

BoardItemAction::BoardItemAction() {};

void BoardItemAction::insert(BoardItemActionRelation relation, int hash) {
    _relations[relation].insert(hash);
};

void BoardItemAction::clear() {
    _relations[BoardItemActionRelation::TO].clear();
    _relations[BoardItemActionRelation::BY].clear();
};

const BoardItemActionHashes& BoardItemAction::get(BoardItemActionRelation relation) const {
    return _relations.at(relation);
};

BoardItemActions::BoardItemActions() {};

void BoardItemActions::insert(BoardItemActionType type, BoardItemActionRelation relation, int hash) {
    _inners[type].insert(relation, hash);
};

void BoardItemActions::clear() {
    _inners[BoardItemActionType::THREAT].clear();
    _inners[BoardItemActionType::SUPPORT].clear();
    _inners[BoardItemActionType::PLACE].clear();
    _inners[BoardItemActionType::XRAY].clear();
};

const BoardItemAction& BoardItemActions::get(BoardItemActionType type) const {
    return _inners.at(type);
};
