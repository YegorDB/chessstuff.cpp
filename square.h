#include <cstdint>
#include <string>
#include <vector>

#include "point.h"

class Square {
static const std::string COLUMN_SIGNS;
static const std::string ROW_SIGNS;
static const std::vector<std::string> COLOR_NAMES;

private:
    std::string name;

public:
    const Point point;
    const bool isLightColor;

    Square(Point point);
    Square(int x, int y);
    Square(std::string name);

    const std::string& getName() const;
    const std::string& getColorName() const;
    const std::string toString() const;
};
