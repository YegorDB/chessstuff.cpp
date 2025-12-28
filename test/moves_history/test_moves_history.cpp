#include "test_moves_history.h"

void testMovesHistoryAddMove() {
    MovesHistory movesHistory{};
    assert_strings_are_equal(movesHistory.toString(), "");

    movesHistory.addMove(
        Move{ PieceType::PAWN, sp("e2"), sp("e4"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(movesHistory.toString(), "1.e4");

    movesHistory.addMove(
        Move{ PieceType::PAWN, sp("e7"), sp("e5"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(movesHistory.toString(), "1.e4 e5");

    movesHistory.addMove(
        Move{ PieceType::KNIGHT, sp("g1"), sp("f3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(movesHistory.toString(), "1.e4 e5 2.Nf3");
}

void testMovesHistory() {
    testHistoryMove();
    testMovesHistoryAddMove();
};
