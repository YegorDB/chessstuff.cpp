#include "test_handler.h"

void testMove() {
    Handler handler1{};
    Handler::Response response1_1 = handler1.move(Point{8, 8}, Point{0, 0});
    assert(!response1_1.isOk());
    assert(response1_1.status == Handler::Response::Status::INVALID_POINT);
    Handler::Response response1_2 = handler1.move(Point{0, 0}, Point{8, 8});
    assert(!response1_2.isOk());
    assert(response1_2.status == Handler::Response::Status::INVALID_POINT);
    Handler::Response response1_3 = handler1.move(Point{3, 3}, Point{4, 4});
    assert(!response1_3.isOk());
    assert(response1_3.status == Handler::Response::Status::PIECE_DOES_NOT_EXIST);
    Handler::Response response1_4 = handler1.move(Point{0, 0}, Point{0, 2});
    assert(!response1_4.isOk());
    assert(response1_4.status == Handler::Response::Status::WRONG_PIECE_COLOR);
    Handler::Response response1_5 = handler1.move(Point{0, 7}, Point{0, 5});
    assert(!response1_5.isOk());
    assert(response1_5.status == Handler::Response::Status::WRONG_DESTINATION);
    Handler::Response response1_6 = handler1.move(Point{0, 7}, Point{0, 1});
    assert(!response1_6.isOk());
    assert(response1_6.status == Handler::Response::Status::WRONG_DESTINATION);

    Handler handler2{FEN{"4k3/8/p7/8/8/7P/8/4K3 w - - 0 1"}};
    Handler::Response response2_1 = handler2.move(Point{4, 7}, Point{4, 6});
    assert(response2_1.isOk());
    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "4k3/8/p7/8/8/7P/4K3/8 b - - 1 1");
    Handler::Response response2_2 = handler2.move(Point{4, 0}, Point{4, 1});
    assert(response2_2.isOk());
    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "8/4k3/p7/8/8/7P/4K3/8 w - - 2 2");

    Handler handler3{FEN{"4kN2/8/p7/8/8/7P/8/4Kn2 w - - 0 1"}};
    Handler::Response response3_1 = handler3.move(Point{4, 7}, Point{5, 7});
    assert(response3_1.isOk());
    assert_strings_are_equal(FEN{handler3.getState()}.getRawString(), "4kN2/8/p7/8/8/7P/8/5K2 b - - 0 1");
    Handler::Response response3_2 = handler3.move(Point{4, 0}, Point{5, 0});
    assert(response3_2.isOk());
    assert_strings_are_equal(FEN{handler3.getState()}.getRawString(), "5k2/8/p7/8/8/7P/8/5K2 w - - 0 2");
}

void testPawnPromotion() {
    Handler handler{FEN{"8/4k2P/8/8/8/8/1p2K3/8 w - - 0 1"}};

    Handler::Response response1 = handler.move(Point{7, 1}, Point{7, 0});
    assert(response1.isOk());
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7P/4k3/8/8/8/8/1p2K3/8 w - - 0 1");
    assert(!handler.getState().pawnPromotion.isUndefined());

    Handler::Response response2 = handler.move(Point{4, 6}, Point{5, 6});
    assert(!response2.isOk());
    assert(response2.status == Handler::Response::Status::WRONG_PAWN_PROMOTION);
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7P/4k3/8/8/8/8/1p2K3/8 w - - 0 1");
    assert(!handler.getState().pawnPromotion.isUndefined());

    Handler::Response response3 = handler.promotePawn(PieceType::KING);
    assert(!response3.isOk());
    assert(response3.status == Handler::Response::Status::WRONG_PAWN_PROMOTION_PIECE_TYPE);
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7P/4k3/8/8/8/8/1p2K3/8 w - - 0 1");
    assert(!handler.getState().pawnPromotion.isUndefined());

    Handler::Response response4 = handler.promotePawn(PieceType::QUEEN);
    assert(response4.isOk());
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7Q/4k3/8/8/8/8/1p2K3/8 b - - 0 1");
    assert(handler.getState().pawnPromotion.isUndefined());

    Handler::Response response5 = handler.promotePawn(PieceType::BISHOP);
    assert(!response5.isOk());
    assert(response5.status == Handler::Response::Status::WRONG_PAWN_PROMOTION);
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7Q/4k3/8/8/8/8/1p2K3/8 b - - 0 1");
    assert(handler.getState().pawnPromotion.isUndefined());

    Handler::Response response6 = handler.move(Point{1, 6}, Point{1, 7});
    assert(response6.isOk());
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7Q/4k3/8/8/8/8/4K3/1p6 b - - 0 1");
    assert(!handler.getState().pawnPromotion.isUndefined());

    Handler::Response response7 = handler.promotePawn(PieceType::QUEEN);
    assert(response7.isOk());
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "7Q/4k3/8/8/8/8/4K3/1q6 w - - 0 2");
    assert(handler.getState().pawnPromotion.isUndefined());
}

void testMoveAndPawnPromotion() {
    testMove();
    testPawnPromotion();
}
