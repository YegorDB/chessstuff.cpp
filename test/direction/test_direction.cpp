#include "test_direction.h"

void testDirection() {
    Direction d{1, 2, 5};
    assert(d.dx == 1);
    assert(d.dy == 2);
    assert(d.maxDistance == 5);
    assert((d == Direction{1, 2, 5}));

    std::cout << "testDirection OK" << std::endl;
}
