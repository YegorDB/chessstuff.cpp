#include "test_history.h"

void testHistoryMovesAddMove() {
    HistoryMoves historyMoves{};
    assert_strings_are_equal(historyMoves.toString(), "");

    historyMoves.addMove(
        HistoryMove{ PieceType::PAWN, sp("e2"), sp("e4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4");

    historyMoves.addMove(
        HistoryMove{ PieceType::PAWN, sp("e7"), sp("e5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4 e5");

    historyMoves.addMove(
        HistoryMove{ PieceType::KNIGHT, sp("g1"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4 e5 2.Nf3");
}

void testHistoryMoves() {
    testHistoryMovesAddMove();
};
