#include "piece.h"
#include "square.h"
#include <iostream>

int main() {
    // Square s{1, 2};
    // std::cout << s.toString() << std::endl;

    // Square s2{"c5"};
    // std::cout << s2.toString() << std::endl;

    // Square s3{"c2"};
    // std::cout << s3.toString() << std::endl;

    // Direction d{1, 2};
    // std::cout << d.dx << " " << d.dy << " " << d.maxDistance << std::endl;

    King k{false};
    std::cout << static_cast<int>(k.type) << " " << k.getColorName() << std::endl;

    auto mdirections = k.getMoveDirections();
    for (auto dd : mdirections) {
        std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    }

    auto adirections = k.getAttackDirections();
    for (auto dd : adirections) {
        std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    }
}
