#include "piece.h"

PiecePlaces::PiecePlaces() {};

PiecePlaces::PiecePlaces(const Items& items) : _items(items) {};

const PiecePlaces::Items& PiecePlaces::getItems() const {
    return _items;
};

const Piece& PiecePlaces::getPiece(const Point& point) const {
    return _items.at(point);
};

bool PiecePlaces::contains(const Point& point) const {
    return _items.contains(point);
};

void PiecePlaces::place(const Point& point, const Piece& piece) {
    _items[point] = piece;
};

void PiecePlaces::move(const Point& from, const Point& to) {
    _items[to] = _items.at(from);
    _items.erase(from);
};
