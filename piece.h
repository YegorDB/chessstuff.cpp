#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "direction.h"

enum class PieceColor {
    WHITE = 0,
    BLACK = 1
};

enum class PieceType {
    KING = 0,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN = 5
};

struct PieceInfo {
    PieceColor color;
    PieceType type;
};

class Piece {
private:
    static const std::vector<std::string> COLOR_NAMES;
    static const std::unordered_map<PieceType, std::vector<Direction>> DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_PLACE_DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_THREAT_DIRECTIONS;

public:
    const PieceType type;
    const bool isWhiteColor;

    Piece(PieceType type, bool isWhiteColor);

    const std::vector<Direction>& getPlaceDirections() const;
    const std::vector<Direction>& getThreatDirections() const;
    const std::string& getColorName() const;
    const bool hasSameColor(const Piece* other) const;
    const bool isKing() const;
};
