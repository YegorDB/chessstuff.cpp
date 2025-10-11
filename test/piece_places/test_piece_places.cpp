#include "test_piece_places.h"

void testPiecePlacesConstructor() {
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
}

void testPiecePlacesPlaceMoveRemove() {
    PiecePlaces pp;

    pp.place(sp("d1"), Piece{PieceType::QUEEN, true});
    pp.place(sp("d8"), Piece{PieceType::QUEEN, false});

    assert((pp.getItems() == PiecePlaces::Items{
        {sp("d1"), Piece{PieceType::QUEEN, true}},
        {sp("d8"), Piece{PieceType::QUEEN, false}},
    }));

    pp.move(sp("d1"), sp("d8"));

    assert(pp.contains(sp("d8")));
    assert((pp.getPiece(sp("d8")).isWhiteColor()));
    assert(!pp.contains(sp("d1")));
    assert(pp.getPiece(sp("d8")).getMovesCount() == 1);

    pp.remove(sp("d8"));
    assert(!pp.contains(sp("d8")));
}

void testPiecePlacesGetKingPoint() {
    PiecePlaces pp;

    assert(pp.getKingPoint(PieceColor::WHITE).isUndefined());
    assert(pp.getKingPoint(PieceColor::BLACK).isUndefined());

    pp.place(sp("e1"), Piece{PieceType::KING, true});
    pp.place(sp("e8"), Piece{PieceType::KING, false});

    assert_points_are_equal(pp.getKingPoint(PieceColor::WHITE), sp("e1"));
    assert_points_are_equal(pp.getKingPoint(PieceColor::BLACK), sp("e8"));

    pp.move(sp("e1"), sp("e2"));
    pp.move(sp("e8"), sp("e7"));

    assert_points_are_equal(pp.getKingPoint(PieceColor::WHITE), sp("e2"));
    assert_points_are_equal(pp.getKingPoint(PieceColor::BLACK), sp("e7"));

    pp.remove(sp("e2"));
    pp.remove(sp("e7"));

    assert(pp.getKingPoint(PieceColor::WHITE).isUndefined());
    assert(pp.getKingPoint(PieceColor::BLACK).isUndefined());
}

void testPiecePlaces() {
    testPiecePlacesConstructor();
    testPiecePlacesPlaceMoveRemove();
    testPiecePlacesGetKingPoint();

    std::cout << "testPiecePlaces OK" << std::endl;
};
