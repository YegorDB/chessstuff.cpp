#include "test_piece_places.h"

void testPiecePlaces() {
    PiecePlaces pp{
        {Point{0, 4}, PieceInfo{PieceColor::WHITE, PieceType::KING}},
        {Point{5, 2}, PieceInfo{PieceColor::BLACK, PieceType::KING}},
    };

    assert((pp.at(Point{0, 4}).color == PieceColor::WHITE));
    assert((pp.at(Point{0, 4}).type == PieceType::KING));
    assert((pp.at(Point{5, 2}).color == PieceColor::BLACK));
    assert((pp.at(Point{5, 2}).type == PieceType::KING));

    std::cout << "testPiecePlaces OK" << std::endl;
};
