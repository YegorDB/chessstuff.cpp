#include "square.h"

Square::Square(uint16_t x, uint16_t y) : x(x), y(y) {
    name = {COLUMN_SIGNS[x], ROW_SIGNS[8 - y]};
    isLightColor = x % 2 == y % 2;
    color = isLightColor ? 0 : 1;
    colorName = COLOR_NAMES[color];
}

Square::Square(std::string name) : Square(name[0] - 97, 56 - name[1]) {}

const std::string& Square::getName() const {
    return name;
}

const bool Square::checkIsLightColor() const {
    return isLightColor;
}

const uint16_t Square::getColor() const {
    return color;
}

const std::string& Square::getColorName() const {
    return colorName;
}

const std::string Square::toString() const {
    return name + " (" + std::to_string(x) + ", " + std::to_string(y) + ") " + colorName;
}
