#include "board_item_action.h"

BoardItemAction::BoardItemAction() {};

void BoardItemAction::clear() {
    to.clear();
    by.clear();
};

void BoardItemAction::insert_to(int hash) {
    to.insert(hash);
};

void BoardItemAction::insert_by(int hash) {
    by.insert(hash);
};

BoardItemActions::BoardItemActions() {};

void BoardItemActions::clear() {
    threat.clear();
    support.clear();
    place.clear();
    xray.clear();
};
