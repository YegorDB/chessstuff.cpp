#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "../direction/direction.h"
#include "../point/point.h"
#include "../square/square.h"

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
    static const std::unordered_map<PieceColor, std::unordered_map<PieceType, std::string>> VISIBLE_SYMBOLS;
    static const std::unordered_map<PieceType, std::vector<Direction>> DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_PLACE_DIRECTIONS;
    static const std::unordered_map<PieceColor, std::vector<Direction>> PAWN_THREAT_DIRECTIONS;

    PieceType _type = PieceType::UNSET;
    PieceColor _color = PieceColor::UNSET;
    int _movesCount = 0;

public:
    static const std::unordered_map<char, std::pair<PieceType, PieceColor>> SYMBOLS_TO_INFO;
    static const std::unordered_map<char, PieceColor> SYMBOLS_TO_COLOR;
    static const std::unordered_map<PieceColor, std::unordered_map<PieceType, char>> INFO_TO_SYMBOLS;
    static const std::unordered_map<PieceColor, char> COLOR_TO_SYMBOLS;
    static const std::unordered_set<PieceType> PAWN_PROMOTION_TYPES;

    Piece();
    Piece(PieceType type, bool isWhiteColor);

    void operator=(const Piece& piece);
    bool operator==(const Piece& piece) const;

    void increaseMovesCount();
    const PieceType getType() const;
    const PieceColor getColor() const;
    const std::vector<Direction>& getPlaceDirections() const;
    const std::vector<Direction>& getThreatDirections() const;
    const std::string& getColorName() const;
    const std::string& getVisibleSymbol() const;
    int getMovesCount() const;
    bool isWhiteColor() const;
    bool hasColor(PieceColor color) const;
    bool hasSameColor(const Piece& other) const;
    bool isKing() const;
    bool isQueen() const;
    bool isRook() const;
    bool isBishop() const;
    bool isKnight() const;
    bool isPawn() const;
    bool isUndefined() const;
};

class PiecePlaces {
public:
    using Items = std::unordered_map<Point, Piece, PointHasher>;
    using KingPoints = std::unordered_map<PieceColor, Point>;

    PiecePlaces();
    PiecePlaces(const Items& items);

    const Items& getItems() const;
    const Piece& getPiece(const Point& point) const;
    const Point& getKingPoint(PieceColor color) const;
    bool contains(const Point& point) const;
    void place(const Point& point, const Piece& piece);
    void move(const Point& from, const Point& to);
    void remove(const Point& point);
private:
    Items _items;
    KingPoints _kingPoints;
    Piece _undefinedPiece;
    Point _undefinedPoint;
};
