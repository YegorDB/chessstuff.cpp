#include "test_moves_history.h"

void testPlaceHistoryMove() {
    Move move1{ PieceType::KING, sp("e1"), sp("e2"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "Ke2");

    Move move2{ PieceType::QUEEN, sp("d8"), sp("d5"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "Qd5");

    Move move3{ PieceType::ROOK, sp("a1"), sp("a3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "Ra3");

    Move move4{ PieceType::BISHOP, sp("f8"), sp("d6"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "Bd6");

    Move move5{ PieceType::KNIGHT, sp("g1"), sp("f3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move5.toString(), "Nf3");

    Move move6{ PieceType::PAWN, sp("e7"), sp("e5"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move6.toString(), "e5");

    Move move7{ PieceType::KING, sp("e7"), sp("d8"), Move::Type::PLACE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move7.toString(), "Kd8+");

    Move move8{ PieceType::QUEEN, sp("d3"), sp("f5"), Move::Type::PLACE, 2, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move8.toString(), "Qf5++");

    Move move9{ PieceType::ROOK, sp("c6"), sp("e6"), Move::Type::PLACE, 2, false, PieceType::UNSET, PointSet{sp("g6")} };
    assert_strings_are_equal(move9.toString(), "Rce6++");

    Move move10{ PieceType::ROOK, sp("c6"), sp("c3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("c1")} };
    assert_strings_are_equal(move10.toString(), "R6c3");

    Move move11{ PieceType::ROOK, sp("c6"), sp("f6"), Move::Type::PLACE, 1, false, PieceType::UNSET, PointSet{sp("f2")} };
    assert_strings_are_equal(move11.toString(), "Rc6f6+");

    Move move12{ PieceType::QUEEN, sp("d5"), sp("f3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f5"), sp("d3")} };
    assert_strings_are_equal(move12.toString(), "Qd5f3");

    Move move13{ PieceType::QUEEN, sp("d5"), sp("f3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f5"), sp("a3")} };
    assert_strings_are_equal(move13.toString(), "Qdf3");

    Move move14{ PieceType::QUEEN, sp("d5"), sp("f3"), Move::Type::PLACE, 0, false, PieceType::UNSET, PointSet{sp("f7"), sp("d3")} };
    assert_strings_are_equal(move14.toString(), "Q5f3");

    Move move15{ PieceType::PAWN, sp("b4"), sp("b5"), Move::Type::PLACE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move15.toString(), "b5#");
};

void testTakeHistoryMove() {
    Move move1{ PieceType::KNIGHT, sp("c3"), sp("e4"), Move::Type::TAKE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "Nxe4");

    Move move2{ PieceType::BISHOP, sp("g7"), sp("c3"), Move::Type::TAKE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "Bxc3+");

    Move move3{ PieceType::ROOK, sp("e4"), sp("b4"), Move::Type::TAKE, 2, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "Rxb4++");

    Move move4{ PieceType::PAWN, sp("a5"), sp("b6"), Move::Type::TAKE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "axb6");

    Move move5{ PieceType::KING, sp("f6"), sp("g6"), Move::Type::TAKE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move5.toString(), "Kxg6#");
};

void testPawnPromotionHistoryMove() {
    Move move1{ PieceType::PAWN, sp("h7"), sp("h8"), Move::Type::PAWN_PROMOTION, 0, false, PieceType::ROOK, PointSet{} };
    assert_strings_are_equal(move1.toString(), "h8=R");

    Move move2{ PieceType::PAWN, sp("c2"), sp("c1"), Move::Type::PAWN_PROMOTION, 1, false, PieceType::BISHOP, PointSet{} };
    assert_strings_are_equal(move2.toString(), "c1=B+");

    Move move3{ PieceType::PAWN, sp("e7"), sp("e8"), Move::Type::PAWN_PROMOTION, 2, false, PieceType::QUEEN, PointSet{} };
    assert_strings_are_equal(move3.toString(), "e8=Q++");

    Move move4{ PieceType::PAWN, sp("d2"), sp("d1"), Move::Type::PAWN_PROMOTION, 1, true, PieceType::KNIGHT, PointSet{} };
    assert_strings_are_equal(move4.toString(), "d1=N#");
};

void testCastleHistoryMove() {
    Move move1{ PieceType::KING, sp("e1"), sp("g1"), Move::Type::KING_SIDE_CASTLE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move1.toString(), "0-0");

    Move move2{ PieceType::KING, sp("e8"), sp("c8"), Move::Type::QUEEN_SIDE_CASTLE, 0, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move2.toString(), "0-0-0");

    Move move3{ PieceType::KING, sp("e1"), sp("g1"), Move::Type::KING_SIDE_CASTLE, 1, false, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move3.toString(), "0-0+");

    Move move4{ PieceType::KING, sp("e8"), sp("c8"), Move::Type::QUEEN_SIDE_CASTLE, 1, true, PieceType::UNSET, PointSet{} };
    assert_strings_are_equal(move4.toString(), "0-0-0#");
};

void testHistoryMove() {
    testPlaceHistoryMove();
    testTakeHistoryMove();
    testPawnPromotionHistoryMove();
    testCastleHistoryMove();
};
