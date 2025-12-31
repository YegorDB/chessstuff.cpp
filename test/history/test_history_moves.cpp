#include "test_history.h"

void testHistoryMovesAddMainLineMove() {
    HistoryMoves historyMoves{};
    assert_strings_are_equal(historyMoves.toString(), "");

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::PAWN, sp("e2"), sp("e4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4");

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::PAWN, sp("e7"), sp("e5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4 e5");

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::KNIGHT, sp("g1"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );
    assert_strings_are_equal(historyMoves.toString(), "1.e4 e5 2.Nf3");
}

void testHistoryMovesAddSideLineMoveThrowError() {
    HistoryMoves historyMoves{};

    assert_error_was_thrown(
        [&](){
            historyMoves.addSideLineMove(
                HistoryMove{ PieceType::PAWN, sp("e2"), sp("e4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} },
                -10
            );
        },
        "Wrong previous item index."
    );

    assert_error_was_thrown(
        [&](){
            historyMoves.addSideLineMove(
                HistoryMove{ PieceType::PAWN, sp("e2"), sp("e4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} },
                10
            );
        },
        "Wrong previous item index."
    );
}

void testHistoryMovesAddSideLineMove() {
    HistoryMoves historyMoves{};

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::PAWN, sp("e2"), sp("e4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );

    historyMoves.addSideLineMove(
        HistoryMove{ PieceType::PAWN, sp("c7"), sp("c5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} },
        historyMoves.getItems().size() - 1
    );

    assert_strings_are_equal(historyMoves.toString(true), "1.e4\n\n1.e4 c5");

    historyMoves.addSideLineMove(
        HistoryMove{ PieceType::PAWN, sp("d2"), sp("d4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} },
        historyMoves.getItems().size() - 1
    );

    assert_strings_are_equal(historyMoves.toString(true), "1.e4\n\n1.e4 c5 2.d4");

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::PAWN, sp("e7"), sp("e5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );

    assert_strings_are_equal(historyMoves.toString(true), "1.e4 e5\n\n1.e4 c5 2.d4");

    historyMoves.addMainLineMove(
        HistoryMove{ PieceType::KNIGHT, sp("g1"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} }
    );

    assert_strings_are_equal(historyMoves.toString(true), "1.e4 e5 2.Nf3\n\n1.e4 c5 2.d4");

    historyMoves.addSideLineMove(
        HistoryMove{ PieceType::BISHOP, sp("f1"), sp("c4"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} },
        historyMoves.getItems().size() - 2
    );

    assert_strings_are_equal(historyMoves.toString(true), "1.e4 e5 2.Nf3\n\n1.e4 c5 2.d4\n\n1.e4 e5 2.Bc4");
}

void testHistoryMoves() {
    testHistoryMovesAddMainLineMove();
    testHistoryMovesAddSideLineMoveThrowError();
    testHistoryMovesAddSideLineMove();
};
