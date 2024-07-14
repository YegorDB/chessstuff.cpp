#include "piece.h"
#include "square.h"
#include <iostream>

int main() {
    Square s{1, 2};
    std::cout << s.toString() << std::endl;

    Square s2{"c5"};
    std::cout << s2.toString() << std::endl;

    Square s3{"c2"};
    std::cout << s3.toString() << std::endl;

    Direction d{1, 2};
    std::cout << d.dx << " " << d.dy << " " << d.maxDistance << std::endl;

    Piece p{PieceType::KING, true};
    std::cout << static_cast<uint16_t>(p.type) << " " << p.getColorName() << std::endl;
}
