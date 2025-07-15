#pragma once

#include <unordered_map>

#include "piece.h"
#include "point.h"

class PiecePlaces {
public:
    using Items = std::unordered_map<Point, Piece, PointHasher>;

    PiecePlaces();
    PiecePlaces(const Items& items);

    const Items& getItems() const;
    const Piece& getPiece(const Point& point) const;
    bool contains(const Point& point) const;
    void place(const Point& point, const Piece& piece);
    void move(const Point& from, const Point& to);
private:
    Items _items;
};
