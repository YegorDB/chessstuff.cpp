#include "test_piece_places.h"

void testPiecePlaces() {
    PiecePlaces pp{
        PiecePlaces::Items{
            {Point{0, 4}, Piece{PieceType::KING, true}},
            {Point{5, 2}, Piece{PieceType::KING, false}},
        }
    };

    assert((pp.getPiece(Point{0, 4}).isWhiteColor()));
    assert((pp.getPiece(Point{0, 4}).getType() == PieceType::KING));
    assert((!pp.getPiece(Point{5, 2}).isWhiteColor()));
    assert((pp.getPiece(Point{5, 2}).getType() == PieceType::KING));

    PiecePlaces pp2;

    pp2.place(Point{3, 6}, Piece{PieceType::QUEEN, true});
    pp2.place(Point{2, 7}, Piece{PieceType::QUEEN, false});

    assert((pp2.getItems() == PiecePlaces::Items{
        {Point{3, 6}, Piece{PieceType::QUEEN, true}},
        {Point{2, 7}, Piece{PieceType::QUEEN, false}},
    }));

    pp2.move(Point{3, 6}, Point{2, 7});

    assert(pp2.contains(Point{2, 7}));
    assert((pp2.getPiece(Point{2, 7}).isWhiteColor()));
    assert(!pp2.contains(Point{3, 6}));

    std::cout << "testPiecePlaces OK" << std::endl;
};
