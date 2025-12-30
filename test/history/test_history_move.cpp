#include "test_history.h"

void testHistoryMovePlace() {
    HistoryMove move1{ PieceType::KING, sp("e1"), sp("e2"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "Ke2");

    HistoryMove move2{ PieceType::QUEEN, sp("d8"), sp("d5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "Qd5");

    HistoryMove move3{ PieceType::ROOK, sp("a1"), sp("a3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "Ra3");

    HistoryMove move4{ PieceType::BISHOP, sp("f8"), sp("d6"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "Bd6");

    HistoryMove move5{ PieceType::KNIGHT, sp("g1"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move5.toString(), "Nf3");

    HistoryMove move6{ PieceType::PAWN, sp("e7"), sp("e5"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move6.toString(), "e5");

    HistoryMove move7{ PieceType::KING, sp("e7"), sp("d8"), HistoryMove::Type::PLACE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move7.toString(), "Kd8+");

    HistoryMove move8{ PieceType::QUEEN, sp("d3"), sp("f5"), HistoryMove::Type::PLACE, 2, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move8.toString(), "Qf5++");

    HistoryMove move9{ PieceType::ROOK, sp("c6"), sp("e6"), HistoryMove::Type::PLACE, 2, false, PieceType::UNSET, PointSet{sp("g6")} };
    assert_strings_are_equal(move9.toString(), "Rce6++");

    HistoryMove move10{ PieceType::ROOK, sp("c6"), sp("c3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("c1")} };
    assert_strings_are_equal(move10.toString(), "R6c3");

    HistoryMove move11{ PieceType::ROOK, sp("c6"), sp("f6"), HistoryMove::Type::PLACE, 1, false, PieceType::UNSET, PointSet{sp("f2")} };
    assert_strings_are_equal(move11.toString(), "Rc6f6+");

    HistoryMove move12{ PieceType::QUEEN, sp("d5"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f5"), sp("d3")} };
    assert_strings_are_equal(move12.toString(), "Qd5f3");

    HistoryMove move13{ PieceType::QUEEN, sp("d5"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f5"), sp("a3")} };
    assert_strings_are_equal(move13.toString(), "Qdf3");

    HistoryMove move14{ PieceType::QUEEN, sp("d5"), sp("f3"), HistoryMove::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f7"), sp("d3")} };
    assert_strings_are_equal(move14.toString(), "Q5f3");

    HistoryMove move15{ PieceType::PAWN, sp("b4"), sp("b5"), HistoryMove::Type::PLACE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move15.toString(), "b5#");
};

void testHistoryMoveTake() {
    HistoryMove move1{ PieceType::KNIGHT, sp("c3"), sp("e4"), HistoryMove::Type::TAKE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "Nxe4");

    HistoryMove move2{ PieceType::BISHOP, sp("g7"), sp("c3"), HistoryMove::Type::TAKE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "Bxc3+");

    HistoryMove move3{ PieceType::ROOK, sp("e4"), sp("b4"), HistoryMove::Type::TAKE, 2, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "Rxb4++");

    HistoryMove move4{ PieceType::PAWN, sp("a5"), sp("b6"), HistoryMove::Type::TAKE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "axb6");

    HistoryMove move5{ PieceType::KING, sp("f6"), sp("g6"), HistoryMove::Type::TAKE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move5.toString(), "Kxg6#");
};

void testHistoryMovePawnPromotion() {
    HistoryMove move1{ PieceType::PAWN, sp("h7"), sp("h8"), HistoryMove::Type::PAWN_PROMOTION, 0, false, PieceType::ROOK, PointSet{} };
    assert_strings_are_equal(move1.toString(), "h8=R");

    HistoryMove move2{ PieceType::PAWN, sp("c2"), sp("c1"), HistoryMove::Type::PAWN_PROMOTION, 1, false, PieceType::BISHOP, PointSet{} };
    assert_strings_are_equal(move2.toString(), "c1=B+");

    HistoryMove move3{ PieceType::PAWN, sp("e7"), sp("e8"), HistoryMove::Type::PAWN_PROMOTION, 2, false, PieceType::QUEEN, PointSet{} };
    assert_strings_are_equal(move3.toString(), "e8=Q++");

    HistoryMove move4{ PieceType::PAWN, sp("d2"), sp("d1"), HistoryMove::Type::PAWN_PROMOTION, 1, true, PieceType::KNIGHT, PointSet{} };
    assert_strings_are_equal(move4.toString(), "d1=N#");
};

void testHistoryMoveCastle() {
    HistoryMove move1{ PieceType::KING, sp("e1"), sp("g1"), HistoryMove::Type::KING_SIDE_CASTLE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "0-0");

    HistoryMove move2{ PieceType::KING, sp("e8"), sp("c8"), HistoryMove::Type::QUEEN_SIDE_CASTLE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "0-0-0");

    HistoryMove move3{ PieceType::KING, sp("e1"), sp("g1"), HistoryMove::Type::KING_SIDE_CASTLE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "0-0+");

    HistoryMove move4{ PieceType::KING, sp("e8"), sp("c8"), HistoryMove::Type::QUEEN_SIDE_CASTLE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "0-0-0#");
};

void testHistoryMove() {
    testHistoryMovePlace();
    testHistoryMoveTake();
    testHistoryMovePawnPromotion();
    testHistoryMoveCastle();
};
