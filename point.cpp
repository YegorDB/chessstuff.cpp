#include "point.h"

Point::Point(int x, int y) : _x(x), _y(y), _hash(y * 10 + x) {};

void Point::operator=(Point other) {
    _x = other._x;
    _y = other._y;
    _hash = other._hash;
};

bool Point::operator==(const Point& other) const {
    return _hash == other._hash;
};

int Point::x() const {
    return _x;
};

int Point::y() const {
    return _y;
};

int Point::hash() const {
    return _hash;
};

Point Point::next(Direction direction) {
    return Point{_x + direction.dx, _y + direction.dy};
};

bool Point::isValid() const {
    return _x >= 0 && _x < 8 && _y >= 0 && _y < 8;
};

const std::string Point::toString() const {
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
};

int PointHasher::operator()(const Point& point) const {
    return point.hash();
};
