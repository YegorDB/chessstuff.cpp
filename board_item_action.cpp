#include "board_item_action.h"

BoardItemAction::BoardItemAction() {};

void BoardItemAction::clear() {
    _to.clear();
    _by.clear();
};

void BoardItemAction::insertTo(int hash) {
    _to.insert(hash);
};

void BoardItemAction::insertBy(int hash) {
    _by.insert(hash);
};

const BoardItemActionHashes& BoardItemAction::getTo() const {
    return _to;
};

const BoardItemActionHashes& BoardItemAction::getBy() const {
    return _by;
};

BoardItemActions::BoardItemActions() {};

void BoardItemActions::clear() {
    _threat.clear();
    _support.clear();
    _place.clear();
    _xray.clear();
};

BoardItemAction& BoardItemActions::getThreat() {
    return _threat;
};

BoardItemAction& BoardItemActions::getSupport() {
    return _support;
};

BoardItemAction& BoardItemActions::getPlace() {
    return _place;
};

BoardItemAction& BoardItemActions::getXray() {
    return _xray;
};
