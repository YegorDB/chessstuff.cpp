#include "board.h"
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

    // Piece k{PieceType::KING, false};
    // std::cout << static_cast<int>(k.type) << " " << k.getColorName() << std::endl;

    // for (auto dd : k.getPlaceDirections()) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    // for (auto dd : k.getThreatDirections()) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    Square s{1, 2};
    Piece pi{PieceType::KING, false};

    BoardItem bi{s, &pi};
    std::cout << bi.square.toString() << std::endl;

    Board b{};
    auto items = b.getItems();

    for (auto row : items) {
        for (auto bi : row) {
            std::cout << bi.square.getName() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << (items[2][3].piece == nullptr) << std::endl;
    std::cout << (items[7][3].piece != nullptr) << std::endl;
    std::cout << (items[0][4].piece != nullptr) << std::endl;

    std::cout << (items[0][4].piece->type == PieceType::KING) << std::endl;
    Piece k3 = *items[0][4].piece;
    std::cout << static_cast<int>(k3.type) << " " << k3.getColorName() << std::endl;

    std::cout << (items[7][3].piece->type == PieceType::QUEEN) << std::endl;
    Piece q3 = *items[7][3].piece;
    std::cout << static_cast<int>(q3.type) << " " << q3.getColorName() << std::endl;
}
