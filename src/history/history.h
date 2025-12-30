#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../piece/piece.h"

class HistoryMove {
private:
    std::string _stringValue;

    void _buidStringValue();

public:
    static const std::unordered_map<PieceType, std::string> PIECE_TYPES_TO_SYMBOLS;

    enum class Type {
        PLACE = 0,
        TAKE = 1,
        PAWN_PROMOTION = 2,
        KING_SIDE_CASTLE = 3,
        QUEEN_SIDE_CASTLE = 4,
    };

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

    const std::string toString() const;
};

class HistoryMoves {
public:
    struct Item {
        const HistoryMove move;
        std::vector<int> nextMoveIndexes;
    };

    void addMove(HistoryMove&& move);
    std::string toString() const;

private:
    std::vector<Item> _items;
};
