#include "handler.h"

void Handler::_countPosition() {
    const std::vector<std::string> fenParts = FEN{_state}.getRawStringParts();

    std::string positionKey = fenParts.at(0);
    for (int i = 1; i < 4; i++) {
        positionKey.push_back(' ');
        positionKey += fenParts.at(i);
    }

    if (_positionCounts.contains(positionKey)) {
        _positionCounts[positionKey]++;
    } else {
        _positionCounts.emplace(positionKey, 1);
    }

    if (_positionCounts.at(positionKey) > _maxPositionCount) {
        _maxPositionCount = _positionCounts.at(positionKey);
    }
};
