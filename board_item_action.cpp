#include "board_item_action.h"

BoardItemAction::BoardItemAction() {};

void BoardItemAction::clear() {
    to.clear();
    by.clear();
};

void BoardItemAction::insertTo(int hash) {
    to.insert(hash);
};

void BoardItemAction::insertBy(int hash) {
    by.insert(hash);
};

const BoardItemActionHashes& BoardItemAction::getTo() const {
    return to;
};

const BoardItemActionHashes& BoardItemAction::getBy() const {
    return by;
};

BoardItemActions::BoardItemActions() {};

void BoardItemActions::clear() {
    threat.clear();
    support.clear();
    place.clear();
    xray.clear();
};
