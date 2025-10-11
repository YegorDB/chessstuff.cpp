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
    if (piece.isKing()) {
        _kingPoints[piece.getColor()] = point;
    }
};

void PiecePlaces::move(const Point& from, const Point& to) {
    if (!_items.contains(from)) {
        throw std::runtime_error{
            std::format("There is no piece to move from {}.", Square{from}.toString())
        };
    }
    _items[to] = _items.at(from);
    _items[to].increaseMovesCount();
    _items.erase(from);

    if (_items.at(to).isKing()) {
        _kingPoints[_items.at(to).getColor()] = to;
    }
};

void PiecePlaces::remove(const Point& point) {
    if (!_items.contains(point)) {
        return;
    }

    if (_items.at(point).isKing()) {
        _kingPoints.erase(_items.at(point).getColor());
    }

    _items.erase(point);
};

const Point& PiecePlaces::getKingPoint(PieceColor color) const {
    if (!_kingPoints.contains(color)) {
        return _undefinedPoint;
    }
    return _kingPoints.at(color);
};
