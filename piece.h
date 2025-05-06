#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "direction.h"

enum class PieceColor {
    UNSET = 0,
    WHITE = 1,
    BLACK = 2
};

enum class PieceType {
    UNSET = 0,
    KING = 1,
    QUEEN = 2,
    ROOK = 3,
    BISHOP = 4,
    KNIGHT = 5,
    PAWN = 6
};

class Piece {
private:
    static const std::vector<std::string> COLOR_NAMES;
    static const std::unordered_map<PieceType, std::vector<Direction>> DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_PLACE_DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_THREAT_DIRECTIONS;

    PieceType _type = PieceType::UNSET;
    PieceColor _color = PieceColor::UNSET;

public:
    Piece();
    Piece(PieceType type, bool isWhiteColor);

    void operator=(const Piece& piece);

    const PieceType getType() const;
    const PieceColor getColor() const;
    const std::vector<Direction>& getPlaceDirections() const;
    const std::vector<Direction>& getThreatDirections() const;
    const std::string& getColorName() const;
    const bool isWhiteColor() const;
    const bool hasSameColor(const Piece& other) const;
    const bool isKing() const;
};
