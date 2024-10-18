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

    // King k{false};
    // std::cout << static_cast<int>(k.type) << " " << k.getColorName() << std::endl;

    // auto mdirections = k.getMoveDirections();
    // for (auto dd : mdirections) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    // auto adirections = k.getAttackDirections();
    // for (auto dd : adirections) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    Square s{1, 2};
    PieceItem pi{King{false}};

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
    King k3 = items[0][4].piece->getKing();
    std::cout << static_cast<int>(k3.type) << " " << k3.getColorName() << std::endl;

    std::cout << (items[7][3].piece->type == PieceType::QUEEN) << std::endl;
    Queen q3 = items[7][3].piece->getQueen();
    std::cout << static_cast<int>(q3.type) << " " << q3.getColorName() << std::endl;
}
