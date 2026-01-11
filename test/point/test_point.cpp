#include "test_point.h"

void testPointObject() {
    Point p{3, 6};
    assert(p.x() == 3 && p.y() == 6 && p.hash() == 63);
    assert((p == Point{3, 6}));
    assert(p.isValid());
    assert(!p.isUndefined());
    assert(p.toString() == "(3, 6)");

    p = p.next(Direction{-1, 2});
    assert(p.x() == 2 && p.y() == 8 && p.hash() == 82);
    assert((p == Point{2, 8}));
    assert(!p.isValid());
    assert(!p.isUndefined());
    assert(p.toString() == "(2, 8)");

    p = Point{};
    assert(p.x() == -1 && p.y() == -1 && p.hash() == -1);
    assert((p == Point{}));
    assert(!p.isValid());
    assert(p.isUndefined());
    assert(p.toString() == "(-1, -1)");
};

void testPointHasher() {
    PointHasher pointHasher;
    assert(pointHasher(Point{5, 2}) == 25);
    assert(pointHasher(Point{}) == -1);
};

void testPointSet() {
    PointSet pointSet{Point{1, 2}};
    assert_strings_are_equal(pointSetToString(pointSet), "((1, 2))");
};

void testPoint() {
    testPointObject();
    testPointHasher();
    testPointSet();

    std::cout << "testPoint OK" << std::endl;
};
