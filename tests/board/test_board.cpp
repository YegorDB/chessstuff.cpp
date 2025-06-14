#include "test_board.h"

void testBoard() {
    Board board{};

    int i = 0;
    for (Square* square : board.squares()) {
        assert((square->point == Point{i % 8, i / 8}));
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        assert((square->point == Point{1 + i, 2 + i}));
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        assert((square->point == Point{1 + i, 2 + i}));
    }
    assert(i == 5);

    std::cout << "testBoard OK" << std::endl;
};
