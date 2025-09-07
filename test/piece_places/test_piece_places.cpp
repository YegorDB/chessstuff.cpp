#include "test_piece_places.h"

void testPiecePlaces() {
    PiecePlaces pp{
        PiecePlaces::Items{
            {sp("e1"), Piece{PieceType::KING, true}},
            {sp("e8"), Piece{PieceType::KING, false}},
        }
    };

    assert((pp.getPiece(sp("e1")).isWhiteColor()));
    assert((pp.getPiece(sp("e1")).getType() == PieceType::KING));
    assert((!pp.getPiece(sp("e8")).isWhiteColor()));
    assert((pp.getPiece(sp("e8")).getType() == PieceType::KING));

    PiecePlaces pp2;

    pp2.place(sp("d1"), Piece{PieceType::QUEEN, true});
    pp2.place(sp("d8"), Piece{PieceType::QUEEN, false});

    assert((pp2.getItems() == PiecePlaces::Items{
        {sp("d1"), Piece{PieceType::QUEEN, true}},
        {sp("d8"), Piece{PieceType::QUEEN, false}},
    }));

    pp2.move(sp("d1"), sp("d8"));

    assert(pp2.contains(sp("d8")));
    assert((pp2.getPiece(sp("d8")).isWhiteColor()));
    assert(!pp2.contains(sp("d1")));
    assert(pp2.getPiece(sp("d8")).getMovesCount() == 1);

    pp2.remove(sp("d8"));
    assert(!pp2.contains(sp("d8")));

    std::cout << "testPiecePlaces OK" << std::endl;
};
