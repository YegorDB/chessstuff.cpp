#include "test_moves_history.h"

void testPlaceHistoryMove() {
    Move move1{ PieceType::KING, sp("e1"), sp("e2"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move1.toString(), "Ke2");

    Move move2{ PieceType::QUEEN, sp("d8"), sp("d5"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move2.toString(), "Qd5");

    Move move3{ PieceType::ROOK, sp("a1"), sp("a3"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move3.toString(), "Ra3");

    Move move4{ PieceType::BISHOP, sp("f8"), sp("d6"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move4.toString(), "Bd6");

    Move move5{ PieceType::KNIGHT, sp("g1"), sp("f3"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move5.toString(), "Nf3");

    Move move6{ PieceType::PAWN, sp("e7"), sp("e5"), Move::Type::PLACE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move6.toString(), "e5");

    Move move7{ PieceType::KING, sp("e7"), sp("d8"), Move::Type::PLACE, false, 1, false, PieceType::UNSET };
    assert_strings_are_equal(move7.toString(), "Kd8+");

    Move move8{ PieceType::QUEEN, sp("d3"), sp("f5"), Move::Type::PLACE, false, 2, false, PieceType::UNSET };
    assert_strings_are_equal(move8.toString(), "Qf5++");

    Move move9{ PieceType::ROOK, sp("c6"), sp("e6"), Move::Type::PLACE, true, 2, false, PieceType::UNSET };
    assert_strings_are_equal(move9.toString(), "Rc6e6++");

    Move move10{ PieceType::PAWN, sp("b4"), sp("b5"), Move::Type::PLACE, false, 1, true, PieceType::UNSET };
    assert_strings_are_equal(move10.toString(), "b5#");
};

void testTakeHistoryMove() {
    Move move1{ PieceType::KNIGHT, sp("c3"), sp("e4"), Move::Type::TAKE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move1.toString(), "Nxe4");

    Move move2{ PieceType::BISHOP, sp("g7"), sp("c3"), Move::Type::TAKE, false, 1, false, PieceType::UNSET };
    assert_strings_are_equal(move2.toString(), "Bxc3+");

    Move move3{ PieceType::ROOK, sp("e4"), sp("b4"), Move::Type::TAKE, false, 2, false, PieceType::UNSET };
    assert_strings_are_equal(move3.toString(), "Rxb4++");

    Move move4{ PieceType::PAWN, sp("a5"), sp("b6"), Move::Type::TAKE, true, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move4.toString(), "a5xb6");

    Move move5{ PieceType::KING, sp("f6"), sp("g6"), Move::Type::TAKE, false, 1, true, PieceType::UNSET };
    assert_strings_are_equal(move5.toString(), "Kxg6#");
};

void testPawnPromotionHistoryMove() {
    Move move1{ PieceType::PAWN, sp("h7"), sp("h8"), Move::Type::PAWN_PROMOTION, false, 0, false, PieceType::ROOK };
    assert_strings_are_equal(move1.toString(), "h8=R");

    Move move2{ PieceType::PAWN, sp("c2"), sp("c1"), Move::Type::PAWN_PROMOTION, false, 1, false, PieceType::BISHOP };
    assert_strings_are_equal(move2.toString(), "c1=B+");

    Move move3{ PieceType::PAWN, sp("e7"), sp("e8"), Move::Type::PAWN_PROMOTION, false, 2, false, PieceType::QUEEN };
    assert_strings_are_equal(move3.toString(), "e8=Q++");

    Move move4{ PieceType::PAWN, sp("d2"), sp("d1"), Move::Type::PAWN_PROMOTION, false, 1, true, PieceType::KNIGHT };
    assert_strings_are_equal(move4.toString(), "d1=N#");
};

void testCastleHistoryMove() {
    Move move1{ PieceType::KING, sp("e1"), sp("g1"), Move::Type::KING_SIDE_CASTLE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move1.toString(), "0-0");

    Move move2{ PieceType::KING, sp("e8"), sp("c8"), Move::Type::QUEEN_SIDE_CASTLE, false, 0, false, PieceType::UNSET };
    assert_strings_are_equal(move2.toString(), "0-0-0");

    Move move3{ PieceType::KING, sp("e1"), sp("g1"), Move::Type::KING_SIDE_CASTLE, false, 1, false, PieceType::UNSET };
    assert_strings_are_equal(move3.toString(), "0-0+");

    Move move4{ PieceType::KING, sp("e8"), sp("c8"), Move::Type::QUEEN_SIDE_CASTLE, false, 1, true, PieceType::UNSET };
    assert_strings_are_equal(move4.toString(), "0-0-0#");
};

void testHistoryMove() {
    testPlaceHistoryMove();
    testTakeHistoryMove();
    testPawnPromotionHistoryMove();
    testCastleHistoryMove();
};
