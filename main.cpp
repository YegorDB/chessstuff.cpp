#include "square.h"
#include <iostream>

void printSquare(const Square& square) {
    std::cout << "x, y: " << square.x << ", " << square.y << std::endl;
    std::cout << "name: " << square.getName() << std::endl;
    std::cout << "is light color: " << square.checkIsLightColor() << std::endl;
    std::cout << "color: " << square.getColor() << std::endl;
    std::cout << "color name: " << square.getColorName() << std::endl;
    std::cout << std::endl;
}

int main() {
    Square s{1, 2};
    printSquare(s);

    Square s2{"c5"};
    printSquare(s2);

    Square s3{"c2"};
    printSquare(s3);
}
