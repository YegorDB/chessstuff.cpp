#include <cstdint>
#include <string>
#include <vector>

class Square {
static const std::string COLUMN_SIGNS;
static const std::string ROW_SIGNS;
static const std::vector<std::string> COLOR_NAMES;

private:
    int color;
    std::string name, colorName;
    bool isLightColor;

public:
    const int x, y;

    Square(int x, int y);
    Square(std::string name);

    const std::string& getName() const;
    const bool checkIsLightColor() const;
    const int getColor() const;
    const std::string& getColorName() const;
    const std::string toString() const;
};
