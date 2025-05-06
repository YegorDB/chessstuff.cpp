#include "test_piece_places.h"

void testPiecePlaces() {
    PiecePlaces pp{
        {Point{0, 4}, Piece{PieceType::KING, true}},
        {Point{5, 2}, Piece{PieceType::KING, false}},
    };

    assert((pp.at(Point{0, 4}).isWhiteColor()));
    assert((pp.at(Point{0, 4}).getType() == PieceType::KING));
    assert((!pp.at(Point{5, 2}).isWhiteColor()));
    assert((pp.at(Point{5, 2}).getType() == PieceType::KING));

    std::cout << "testPiecePlaces OK" << std::endl;
};
