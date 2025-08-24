#include "piece.h"

PiecePlaces::PiecePlaces() {};

PiecePlaces::PiecePlaces(const Items& items) : _items(items) {};

const PiecePlaces::Items& PiecePlaces::getItems() const {
    return _items;
};

const Piece& PiecePlaces::getPiece(const Point& point) const {
    if (_items.contains(point)) {
        return _items.at(point);
    }
    return _undefinedPiece;
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

void PiecePlaces::remove(const Point& point) {
    _items.erase(point);
};
