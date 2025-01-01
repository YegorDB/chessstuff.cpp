#include "square.h"

const std::string Square::COLUMN_SIGNS{"abcdefgh"};
const std::string Square::ROW_SIGNS{"012345678"};
const std::vector<std::string> Square::COLOR_NAMES{"light", "dark"};

Square::Square(Point p) : point(p), isLightColor(p.x() % 2 == p.y() % 2) {
    name = {COLUMN_SIGNS[p.x()], ROW_SIGNS[8 - p.y()]};
}

Square::Square(int x, int y) : Square(Point{x, y}) {}

Square::Square(std::string name) : Square(name[0] - 97, 56 - name[1]) {}

const std::string& Square::getName() const {
    return name;
}

const std::string& Square::getColorName() const {
    return COLOR_NAMES[isLightColor ? 0 : 1];
}

const std::string Square::toString() const {
    return name + " " + point.toString() + " " + getColorName();
}
