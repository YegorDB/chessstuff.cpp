#include "history.h"

HistoryMoves::HistoryMoves() {};

void HistoryMoves::addMainLineMove(HistoryMove&& historyMove) {
    int currentIndex = _items.size();
    /**
     * First main line leaf item index always is -1 to be able to add side line before add next main line item.
     * Examples:
     * 1.
     *   [main line] 0 (e4) -> 1 (e5) -> -1 (reserved to next main line item)
     *   [side line]                 \-> 2 (Nf3) -> 3 (Nc6)
     * 2.
     *   [main line] 0 (e4) -> 1 (e5) -> 4 (Bc4) -> -1
     *   [side line]                 \-> 2 (Nf3) -> 3 (Nc6)
     */
    _items.push_back(Item{historyMove, {-1}});
    if (currentIndex > 0) {
        Item& prevItem = _items[_latestMainLineIndex];
        prevItem.nextIndexes[0] = currentIndex;
    }
    _latestMainLineIndex = currentIndex;
}

void HistoryMoves::addSideLineMove(HistoryMove&& historyMove, int prevItemIndex) {
    if (prevItemIndex < 0 || _items.size() <= prevItemIndex) {
        throw std::runtime_error("Wrong previous item index.");
    }

    int currentIndex = _items.size();
    _items.push_back(Item{historyMove});
    Item& prevItem = _items[prevItemIndex];
    prevItem.nextIndexes.push_back(currentIndex);
};

std::string HistoryMoves::toString(bool withSideLines) const {
    if (_items.empty()) {
        return "";
    }

    std::vector<std::string> stringLinesValues;
    std::queue<StringBuilderItem> stringBuilderItems;
    stringBuilderItems.push(StringBuilderItem{0, 0, ""});

    while(!stringBuilderItems.empty()) {
        StringBuilderItem& stringBuilderItem = stringBuilderItems.front();

        Item item = _items.at(stringBuilderItem.currentIndex);

        if (!stringBuilderItem.stringValue.empty()) {
            stringBuilderItem.stringValue += " ";
        }
        if (stringBuilderItem.counter % 2 == 0) {
            stringBuilderItem.stringValue += std::to_string(stringBuilderItem.counter / 2 + 1);
            stringBuilderItem.stringValue.push_back('.');
        }
        stringBuilderItem.stringValue += item.historyMove.toString();

        if (item.nextIndexes.empty() || item.nextIndexes.at(0) == -1) {
            stringLinesValues.push_back(stringBuilderItem.stringValue);
            stringBuilderItems.pop();
        }

        if (!item.nextIndexes.empty()) {
            stringBuilderItem.currentIndex = item.nextIndexes.at(0);
            stringBuilderItem.counter++;

            if (withSideLines && item.nextIndexes.size() > 1) {
                for (int i = 1; i < item.nextIndexes.size(); i++) {
                    stringBuilderItems.push(StringBuilderItem{item.nextIndexes.at(i), stringBuilderItem.counter, stringBuilderItem.stringValue});
                }
            }
        }
    }

    std::string stringValue;
    for (std::string s : stringLinesValues) {
        if (!stringValue.empty()) {
            stringValue += "\n\n";
        }
        stringValue += s;
    }

    return stringValue;
};

const std::vector<HistoryMoves::Item>& HistoryMoves::getItems() const {
    return _items;
};
