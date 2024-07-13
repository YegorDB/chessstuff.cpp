#include <cstdint>
#include <string>
#include <vector>

class Square {
private:
    const std::string COLUMN_SIGNS{"abcdefgh"};
    const std::string ROW_SIGNS{"012345678"};
    const std::vector<std::string> COLOR_NAMES = {"light", "dark"};

    uint16_t color;
    std::string name, colorName;
    bool isLightColor;

public:
    const uint16_t x, y;

    Square(uint16_t x, uint16_t y);
    Square(std::string name);

    const std::string getName() const;
    const bool checkIsLightColor() const;
    const uint16_t getColor() const;
    const std::string getColorName() const;
    const std::string toString() const;
};
