#include "test_board.h"

void testBoard() {
    int i = 0;
    for (Point* point : Board::points()) {
        Point expectedPoint{i % 8, i / 8};
        assert_points_are_equal(*point, expectedPoint);
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (Point* point : Board::pointsByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        Point expectedPoint{1 + i, 2 + i};
        assert_points_are_equal(*point, expectedPoint);
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (Point* point : Board::pointsByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        Point expectedPoint{1 + i, 2 + i};
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 5);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{6, 3})) {
        ++i;
        Point expectedPoint{2 + i, 3};
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 5);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 7}, Point{2, 5})) {
        ++i;
        Point expectedPoint{2, 7 - i};
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 7);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{4, 5})) {
        ++i;
        Point expectedPoint{2 + i, 3 + i};
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 4);

    std::cout << "testBoard OK" << std::endl;
};
