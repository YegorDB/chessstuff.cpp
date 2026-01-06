#include "test_handler.h"

void testCheckIsCheckmate() {
    Handler handler1{FEN{"3k2R1/8/3K4/8/8/8/8/8 b - - 0 0"}};
    assert(handler1.getState().result.type == State::Result::Type::CHECKMATE);
    assert(handler1.getState().result.winnerColor == PieceColor::WHITE);
    assert(handler1.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler::Response response1 = handler1.move(sp("d8"), sp("c8"));
    assert(!response1.isOk());
    assert(response1.status == Handler::Response::Status::RESULT_REACHED);

    Handler handler2{FEN{"3kR3/8/3K4/8/8/8/8/8 b - - 0 0"}};
    assert(handler2.getState().result.type == State::Result::Type::UNSET);
    assert(handler2.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler2.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler3{FEN{"3k2R1/8/3K4/8/8/4r3/8/8 b - - 0 0"}};
    assert(handler3.getState().result.type == State::Result::Type::UNSET);
    assert(handler3.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler3.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler4{FEN{"3k2R1/8/3K4/8/8/1b6/8/8 b - - 0 0"}};
    assert(handler4.getState().result.type == State::Result::Type::UNSET);
    assert(handler4.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler4.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler5{FEN{"2k2R2/8/3K4/8/8/8/8/8 b - - 0 0"}};
    assert(handler5.getState().result.type == State::Result::Type::UNSET);
    assert(handler5.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler5.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler6{FEN{"2k2R2/1R6/3K4/8/8/8/8/8 b - - 0 0"}};
    assert(handler6.getState().result.type == State::Result::Type::UNSET);
    assert(handler6.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler6.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler7{FEN{"8/8/8/1b6/4r3/2k5/3b1N2/3QK3 w - - 0 0"}};
    assert(handler7.getState().result.type == State::Result::Type::CHECKMATE);
    assert(handler7.getState().result.winnerColor == PieceColor::BLACK);
    assert(handler7.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler::Response response2 = handler7.move(sp("f2"), sp("e4"));
    assert(!response2.isOk());
    assert(response2.status == Handler::Response::Status::RESULT_REACHED);

    Handler handler8{FEN{"8/8/8/8/4r3/2k5/3b1N2/3QK3 w - - 0 0"}};
    assert(handler8.getState().result.type == State::Result::Type::UNSET);
    assert(handler8.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler8.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler9{FEN{"8/8/8/8/4r3/2k5/3b1N2/3QKn2 w - - 0 0"}};
    assert(handler9.getState().result.type == State::Result::Type::UNSET);
    assert(handler9.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler9.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler10{FEN{"3k4/8/3K2R1/8/8/8/8/8 w - - 0 0"}};
    Handler::Response response3 = handler10.move(sp("g6"), sp("g8"));
    assert(response3.isOk());
    assert(handler10.getState().result.type == State::Result::Type::CHECKMATE);
    assert(handler10.getState().result.winnerColor == PieceColor::WHITE);
    assert(handler10.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler11{FEN{"8/8/8/1b6/4r3/2k1b3/5N2/3QK3 b - - 0 0"}};
    Handler::Response response4 = handler11.move(sp("e3"), sp("d2"));
    assert(response4.isOk());
    assert(handler11.getState().result.type == State::Result::Type::CHECKMATE);
    assert(handler11.getState().result.winnerColor == PieceColor::BLACK);
    assert(handler11.getState().result.drawType == State::Result::DrawType::UNSET);
}

void testCheckIsStalemate() {
    Handler handler{FEN{"8/8/8/8/p7/Pp6/1P6/K1k5 w - - 0 0"}};
    assert(handler.getState().result.type == State::Result::Type::DRAW);
    assert(handler.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler.getState().result.drawType == State::Result::DrawType::STALEMATE);

    Handler::Response response = handler.move(sp("b2"), sp("b3"));
    assert(!response.isOk());
    assert(response.status == Handler::Response::Status::RESULT_REACHED);
}

void testCheckIsInsufficientMaterial() {
    Handler handler1{FEN{"4k3/8/8/8/8/8/8/4K3 w - - 0 1"}};
    assert(handler1.getState().result.type == State::Result::Type::DRAW);
    assert(handler1.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler1.getState().result.drawType == State::Result::DrawType::INSUFFICIENT_MATERIAL);

    Handler handler2{FEN{"4k3/8/8/8/8/5B2/8/4K3 w - - 0 1"}};
    assert(handler2.getState().result.type == State::Result::Type::DRAW);
    assert(handler2.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler2.getState().result.drawType == State::Result::DrawType::INSUFFICIENT_MATERIAL);

    Handler handler3{FEN{"4k3/8/8/2n5/8/8/8/4K3 w - - 0 1"}};
    assert(handler3.getState().result.type == State::Result::Type::DRAW);
    assert(handler3.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler3.getState().result.drawType == State::Result::DrawType::INSUFFICIENT_MATERIAL);

    Handler handler4{FEN{"4k3/8/8/2b5/8/5B2/8/4K3 w - - 0 1"}};
    assert(handler4.getState().result.type == State::Result::Type::UNSET);
    assert(handler4.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler4.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler5{FEN{"4k3/8/3q4/8/8/8/8/4K3 w - - 0 1"}};
    assert(handler5.getState().result.type == State::Result::Type::UNSET);
    assert(handler5.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler5.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler6{FEN{"4k3/8/3q4/8/8/8/8/4K3 w - - 0 1"}};
    assert(handler6.getState().result.type == State::Result::Type::UNSET);
    assert(handler6.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler6.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler7{FEN{"4k3/8/8/8/8/6R1/8/4K3 w - - 0 1"}};
    assert(handler7.getState().result.type == State::Result::Type::UNSET);
    assert(handler7.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler7.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler handler8{FEN{"4k3/8/1p6/8/8/8/8/4K3 w - - 0 1"}};
    assert(handler8.getState().result.type == State::Result::Type::UNSET);
    assert(handler8.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler8.getState().result.drawType == State::Result::DrawType::UNSET);
}

void testCheckIsFiftyMoveRule() {
    Handler handler{FEN{"8/8/5b1R/3k4/1r6/8/3KB3/8 b - - 99 1"}};
    assert(handler.getState().result.type == State::Result::Type::UNSET);
    assert(handler.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler.getState().result.drawType == State::Result::DrawType::UNSET);

    Handler::Response response1 = handler.move(sp("f6"), sp("e5"));
    assert(response1.isOk());
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "8/8/7R/3kb3/1r6/8/3KB3/8 w - - 100 2");
    assert(handler.getState().result.type == State::Result::Type::DRAW);
    assert(handler.getState().result.winnerColor == PieceColor::UNSET);
    assert(handler.getState().result.drawType == State::Result::DrawType::FIFTY_MOVE_RULE);

    Handler::Response response2 = handler.move(sp("h6"), sp("h3"));
    assert(!response2.isOk());
    assert(response2.status == Handler::Response::Status::RESULT_REACHED);
}

void testCheckIsThreefoldRepetition() {
    Handler handler{FEN{"3qk3/8/8/8/8/8/8/3QK3 w - - 0 1"}};

    Handler::Response response1 = handler.move(sp("e1"), sp("e2"));
    assert(response1.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response2 = handler.move(sp("e8"), sp("e7"));
    assert(response2.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response3 = handler.move(sp("e2"), sp("e1"));
    assert(response3.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response4 = handler.move(sp("e7"), sp("e8"));
    assert(response4.isOk());
    assert(handler.getMaxPositionCount() == 2);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response5 = handler.move(sp("e1"), sp("e2"));
    assert(response5.isOk());
    assert(handler.getMaxPositionCount() == 2);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response6 = handler.move(sp("e8"), sp("e7"));
    assert(response6.isOk());
    assert(handler.getMaxPositionCount() == 2);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response7 = handler.move(sp("e2"), sp("e1"));
    assert(response7.isOk());
    assert(handler.getMaxPositionCount() == 2);
    assert(handler.getState().result.type == State::Result::Type::UNSET);

    Handler::Response response8 = handler.move(sp("e7"), sp("e8"));
    assert(response8.isOk());
    assert(handler.getMaxPositionCount() == 3);
    assert(handler.getState().result.type == State::Result::Type::DRAW);
    assert(handler.getState().result.drawType == State::Result::DrawType::THREEFOLD_REPETITION);
}

void testSetResult() {
    testCheckIsCheckmate();
    testCheckIsStalemate();
    testCheckIsInsufficientMaterial();
    testCheckIsFiftyMoveRule();
    testCheckIsThreefoldRepetition();
}
