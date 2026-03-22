#include "test_piece_places.h"

void testPiecePlacesConstructor() {
    PiecePlaces pp{
        PiecePlaces::Items{
            {sp("e1"), Piece{Piece::Type::KING, true}},
            {sp("e8"), Piece{Piece::Type::KING, false}},
        }
    };

    assert((pp.getPiece(sp("e1")).isWhiteColor()));
    assert((pp.getPiece(sp("e1")).getType() == Piece::Type::KING));
    assert((!pp.getPiece(sp("e8")).isWhiteColor()));
    assert((pp.getPiece(sp("e8")).getType() == Piece::Type::KING));
}

void testPiecePlacesPlaceMoveRemove() {
    PiecePlaces pp;

    pp.place(sp("d1"), Piece{Piece::Type::QUEEN, true});
    pp.place(sp("d8"), Piece{Piece::Type::QUEEN, false});

    assert((pp.getItems() == PiecePlaces::Items{
        {sp("d1"), Piece{Piece::Type::QUEEN, true}},
        {sp("d8"), Piece{Piece::Type::QUEEN, false}},
    }));

    pp.move(sp("d1"), sp("d8"));

    assert(pp.contains(sp("d8")));
    assert((pp.getPiece(sp("d8")).isWhiteColor()));
    assert(!pp.contains(sp("d1")));
    assert(pp.getPiece(sp("d8")).getMovesCount() == 1);

    pp.remove(sp("d8"));
    assert(!pp.contains(sp("d8")));

    assert_error_was_thrown(
        [&](){
            pp.move(sp("d8"), sp("d1"));
        },
        "There is no piece to move from d8."
    );
}

void testPiecePlacesGetKingPoint() {
    PiecePlaces pp;

    assert(pp.getKingPoint(Piece::Color::WHITE).isUndefined());
    assert(pp.getKingPoint(Piece::Color::BLACK).isUndefined());

    pp.place(sp("e1"), Piece{Piece::Type::KING, true});
    pp.place(sp("e8"), Piece{Piece::Type::KING, false});

    assert_points_are_equal(pp.getKingPoint(Piece::Color::WHITE), sp("e1"));
    assert_points_are_equal(pp.getKingPoint(Piece::Color::BLACK), sp("e8"));

    pp.move(sp("e1"), sp("e2"));
    pp.move(sp("e8"), sp("e7"));

    assert_points_are_equal(pp.getKingPoint(Piece::Color::WHITE), sp("e2"));
    assert_points_are_equal(pp.getKingPoint(Piece::Color::BLACK), sp("e7"));

    pp.remove(sp("e2"));
    pp.remove(sp("e7"));

    assert(pp.getKingPoint(Piece::Color::WHITE).isUndefined());
    assert(pp.getKingPoint(Piece::Color::BLACK).isUndefined());
}

void testPiecePlaces() {
    testPiecePlacesConstructor();
    testPiecePlacesPlaceMoveRemove();
    testPiecePlacesGetKingPoint();

    std::cout << "testPiecePlaces OK" << std::endl;
};
