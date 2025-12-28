#include "test_square.h"

void testSquare() {
    Square s1{Point{7, 3}};
    assert((s1.point == Point{7, 3}));
    assert(s1.isLightColor);
    assert(s1.getName() == "h5");
    assert(s1.getFile() == 'h');
    assert(s1.getRank() == '5');
    assert(s1.getColorName() == "light");
    assert(s1.toString() == "h5 (7, 3) light");

    Square s2{1, 4};
    assert((s2.point == Point{1, 4}));
    assert(!s2.isLightColor);
    assert(s2.getName() == "b4");
    assert(s2.getFile() == 'b');
    assert(s2.getRank() == '4');
    assert(s2.getColorName() == "dark");
    assert(s2.toString() == "b4 (1, 4) dark");

    Square s3{"d1"};
    assert((s3.point == Point{3, 7}));
    assert(s3.isLightColor);
    assert(s3.getName() == "d1");
    assert(s3.getFile() == 'd');
    assert(s3.getRank() == '1');
    assert(s3.getColorName() == "light");
    assert(s3.toString() == "d1 (3, 7) light");

    std::cout << "testSquare OK" << std::endl;
};
