#include <stdexcept>

#include "square.h"

const std::string Square::FILE_SIGNS{"abcdefgh"};
const std::string Square::RANK_SIGNS{"012345678"};
const std::vector<std::string> Square::COLOR_NAMES{"light", "dark"};

Point Square::nameToPoint(const std::string& name) {
    if (name.size() != 2 || name[0] < 97 || name[0] > 104 || name[1] < 49 || name[1] > 56) {
        throw std::runtime_error{"Wrong square name."};
    }
    return Point{name[0] - 97, 56 - name[1]};
};

Square::Square(const Point& p) : point(p), isLightColor(p.x() % 2 == p.y() % 2) {
    _name = {getFile(), getRank()};
};

Square::Square(int x, int y) : Square(Point{x, y}) {};

Square::Square(const std::string& name) : Square(nameToPoint(name)) {};

const std::string& Square::getName() const {
    return _name;
};

const char Square::getFile() const {
    return FILE_SIGNS.at(point.x());
};

const char Square::getRank() const {
    return RANK_SIGNS.at(8 - point.y());
};

const std::string& Square::getColorName() const {
    return COLOR_NAMES[isLightColor ? 0 : 1];
};

const std::string Square::toString() const {
    return _name + " " + point.toString() + " " + getColorName();
};

Point sp(const std::string& name) {
    return Square::nameToPoint(name);
};
