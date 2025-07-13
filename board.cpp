#include <stdexcept>

#include "board.h"

Board::Points Board::points() {
    return Points{
        Points::Iterator{0},
        Points::Iterator{64},
    };
};

Board::Points::Points(
    Board::Points::Iterator begin,
    Board::Points::Iterator end
) : _begin{begin}, _end{end} {};

Board::Points::Iterator Board::Points::begin() const {
    return _begin;
};

Board::Points::Iterator Board::Points::end() const {
    return _end;
};

Board::Points::Iterator::Iterator(int index) : _index{index}, _point{Point{index % 8, index / 8}} {};

Board::Points::Iterator& Board::Points::Iterator::operator++() {
    nextStep();
    return *this;
};

Point* Board::Points::Iterator::operator*() {
    return &_point;
};

bool Board::Points::Iterator::operator==(const Board::Points::Iterator& other) const {
    return this->_index == other._index;
};

bool Board::Points::Iterator::operator!=(const Board::Points::Iterator& other) const {
    return this->_index != other._index;
};

void Board::Points::Iterator::nextStep() {
    ++_index;
    _point = Point{_index % 8, _index / 8};
};


Board::PointsByDirection Board::pointsByDirection(const Point& point, const Direction& direction, bool withStartPoint) {
    return PointsByDirection{
        Board::PointsByDirection::Iterator{point, direction, withStartPoint},
        Board::PointsByDirection::Iterator{Point{}, direction, true},
    };
};

Board::PointsByDirection::PointsByDirection(
    Board::PointsByDirection::Iterator begin,
    Board::PointsByDirection::Iterator end
) : _begin{begin}, _end{end} {};

Board::PointsByDirection::Iterator Board::PointsByDirection::begin() const {
    return _begin;
};

Board::PointsByDirection::Iterator Board::PointsByDirection::end() const {
    return _end;
};

Board::PointsByDirection::Iterator::Iterator(
    const Point& point,
    const Direction& direction,
    bool withStartPoint
) : _point{point}, _direction{direction} {
    if (!withStartPoint) {
        nextStep();
    }
};

Board::PointsByDirection::Iterator& Board::PointsByDirection::Iterator::operator++() {
    nextStep();
    return *this;
};

Point* Board::PointsByDirection::Iterator::operator*() {
    return &_point;
};

bool Board::PointsByDirection::Iterator::operator==(const Board::PointsByDirection::Iterator& other) const {
    return this->_point == other._point;
};

bool Board::PointsByDirection::Iterator::operator!=(const Board::PointsByDirection::Iterator& other) const {
    return !(this->_point == other._point);
};

void Board::PointsByDirection::Iterator::nextStep() {
    _point = _point.next(_direction);
    ++_distance;
    if (!_point.isValid() || _distance > _direction.maxDistance) {
        _point = Point{};
    }
};
