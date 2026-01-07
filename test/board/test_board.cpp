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
    assert(i == 3);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 7}, Point{2, 5}, true, true)) {
        Point expectedPoint{2, 7 - i};
        ++i;
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 3);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{4, 5}, true, true)) {
        Point expectedPoint{2 + i, 3 + i};
        ++i;
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 3);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{2, 3})) {
        ++i;
    }
    assert(i == 0);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{2, 4}, true, true)) {
        Point expectedPoint{2, 3 + i};
        ++i;
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 2);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{2, 4}, false, true)) {
        ++i;
        Point expectedPoint{2, 3 + i};
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 1);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{2, 4}, true, false)) {
        Point expectedPoint{2, 3 + i};
        ++i;
        assert_points_are_equal(*point, expectedPoint);
    }
    assert(i == 1);

    i = 0;
    for (Point* point : Board::pointsByTwoPoints(Point{2, 3}, Point{2, 4}, false, false)) {
        ++i;
    }
    assert(i == 0);

    assert_error_was_thrown(
        [](){
            Board::pointsByTwoPoints(Point{1, 1}, Point{2, 4}, true, true);
        },
        "Points are not on the same line."
    );

    std::cout << "testBoard OK" << std::endl;
};
