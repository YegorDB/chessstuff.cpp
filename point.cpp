#include "point.h"

Point::Point(int x, int y) : x(x), y(y) {}

Point Point::next(int dx, int dy) {
    return Point{x + dx, y + dy};
}

bool Point::isValid() {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

const std::string Point::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}
