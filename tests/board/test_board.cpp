#include "test_board.h"

void testBoard() {
    int i = 0;
    for (Point* point : Board::points()) {
        assert((*point == Point{i % 8, i / 8}));
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (Point* point : Board::pointsByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        assert((*point == Point{1 + i, 2 + i}));
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (Point* point : Board::pointsByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        assert((*point == Point{1 + i, 2 + i}));
    }
    assert(i == 5);

    std::cout << "testBoard OK" << std::endl;
};
