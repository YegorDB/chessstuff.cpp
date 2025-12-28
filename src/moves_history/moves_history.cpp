#include "moves_history.h"

void MovesHistory::addMove(Move&& move) {
    _items.push_back(Item{move});
    if (_items.size() > 1) {
        _items[_items.size() - 2].nextMoveIndexes.push_back(_items.size() - 1);
    }
}

std::string MovesHistory::toString() const {
    std::string _stringValue;
    if (_items.size() > 0) {
        int index = 0;
        while(true) {
            if (!_stringValue.empty()) {
                _stringValue += " ";
            }
            if (index % 2 == 0) {
                _stringValue += std::to_string(index / 2 + 1);
                _stringValue.push_back('.');
            }
            const Item& item = _items.at(index);
            _stringValue += item.move.toString();

            if (_items.at(index).nextMoveIndexes.empty()) {
                break;
            }
            index = item.nextMoveIndexes.at(0);
        };
    }
    return _stringValue;
};
