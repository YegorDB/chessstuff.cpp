#pragma once

#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

#include "../piece/piece.h"

class HistoryMove {
public:
    static const std::unordered_map<PieceType, std::string> PIECE_TYPES_TO_SYMBOLS;

    enum class Type {
        PLACE = 0,
        TAKE = 1,
        PAWN_PROMOTION = 2,
        KING_SIDE_CASTLE = 3,
        QUEEN_SIDE_CASTLE = 4,
    };

    HistoryMove();
    HistoryMove(
        PieceType pieceType,
        Point from,
        Point to,
        Type type,
        int checkersCount,
        bool isCheckMate,
        PieceType promotionType,
        PointSet otherCandidates
    );

    PieceType pieceType;
    Point from;
    Point to;
    Type type;
    int checkersCount;
    bool isCheckMate;
    PieceType promotionType;
    PointSet otherCandidates;

    void operator=(const HistoryMove& other);
    std::string toString() const;
};

class HistoryMoves {
public:
    struct Item {
        const HistoryMove historyMove;
        // First next index of main line item is the next main line item index.
        std::vector<int> nextIndexes;
    };

    struct StringBuilderItem {
        int currentIndex;
        int counter;
        std::string stringValue;
    };

    HistoryMoves();

    void addMainLineMove(HistoryMove&& historyMove);
    void addSideLineMove(HistoryMove&& historyMove, int prevItemIndex);
    std::string toString(bool withSideLines = false) const;
    const std::vector<Item>& getItems() const;

private:
    std::vector<Item> _items;
    int _latestMainLineIndex = -1;
};
