#include "test_square.h"

void testSquare() {
    Square s1{Point{7, 3}};
    assert((s1.point == Point{7, 3}));
    assert(s1.isLightColor);
    assert(s1.getName() == "h5");
    assert(s1.getColorName() == "light");
    assert(s1.toString() == "h5 (7, 3) light");

    Square s2{1, 4};
    assert((s2.point == Point{1, 4}));
    assert(!s2.isLightColor);
    assert(s2.getName() == "b4");
    assert(s2.getColorName() == "dark");
    assert(s2.toString() == "b4 (1, 4) dark");

    Square s3{"d1"};
    assert((s3.point == Point{3, 7}));
    assert(s3.isLightColor);
    assert(s3.getName() == "d1");
    assert(s3.getColorName() == "light");
    assert(s3.toString() == "d1 (3, 7) light");

    Square emptySquare{"a1"};
    assert((emptySquare.point == Point{0, 7}));
    assert(!Square::hasPiece(emptySquare));

    Piece king{PieceType::KING, true};
    Square square{"b8", &king};
    assert((square.point == Point{1, 0}));
    assert(square.getPiece()->isKing());
    assert(square.getPiece()->isWhiteColor);
    assert(Square::hasPiece(square));

    std::cout << "testSquare OK" << std::endl;
};
