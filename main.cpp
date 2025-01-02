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

    Square s4{1, 2};
    Piece pi{PieceType::KING, false};

    BoardItem bi{s4, &pi};
    std::cout << bi.square.toString() << std::endl;

    Board b{};
    auto items = b.getItems();

    int i = 0;
    for (auto item : items.sequence()) {
        std::cout << item->square.getName() << " ";
        if (++i % 8 == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;

    i = 0;
    for (auto item : items.sequenceWithPieces()) {
        std::cout << item->square.getName() << " ";
        if (++i % 8 == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;

    std::cout << (items.getItem(Point{3, 2}).piece == nullptr) << std::endl;
    std::cout << (items.getItem(Point{3, 7}).piece != nullptr) << std::endl;
    std::cout << (items.getItem(Point{4, 0}).piece != nullptr) << std::endl;

    std::cout << (items.getItem(Point{4, 0}).piece->type == PieceType::KING) << std::endl;
    Piece k3 = *items.getItem(Point{4, 0}).piece;
    std::cout << static_cast<int>(k3.type) << " " << k3.getColorName() << std::endl;

    std::cout << (items.getItem(Point{3, 7}).piece->type == PieceType::QUEEN) << std::endl;
    Piece q3 = *items.getItem(Point{3, 7}).piece;
    std::cout << static_cast<int>(q3.type) << " " << q3.getColorName() << std::endl;

    Point point{0, 0};
    std::cout << point.toString() << std::endl;
    point = point.next(Direction{2, 2});
    std::cout << point.toString() << std::endl;
}
