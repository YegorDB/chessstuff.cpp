#include "point.h"

Point::Point() : _x(-1), _y(-1), _hash(-1), _undefined(true) {};

Point::Point(int x, int y) : _x(x), _y(y), _hash(y * 10 + x) {};

void Point::operator=(const Point& other) {
    _x = other._x;
    _y = other._y;
    _hash = other._hash;
    _undefined = other._undefined;
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

Point Point::next(const Direction& direction) const {
    return Point{_x + direction.dx, _y + direction.dy};
};

bool Point::isValid() const {
    return _x >= 0 && _x < 8 && _y >= 0 && _y < 8;
};

bool Point::isUndefined() const {
    return _undefined;
};

const std::string Point::toString() const {
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
};

int PointHasher::operator()(const Point& point) const {
    return point.hash();
};

const std::string pointSetToString(const PointSet& pointSet) {
    std::string res = "(";
    for (const Point& point : pointSet) {
        res += point.toString();
    }
    res += ")";
    return res;
};
