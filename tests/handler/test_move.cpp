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

    Handler handler2{FEN{"4k3/8/8/8/8/8/8/4K3 w - - 0 0"}};
    Handler::Response response2_1 = handler2.move(Point{4, 7}, Point{4, 6});
    assert(response2_1.isOk());
    assert((FEN{handler2.getState()}.getRawString() == "4k3/8/8/8/8/8/4K3/8 b - - 0 0"));
    Handler::Response response2_2 = handler2.move(Point{4, 0}, Point{4, 1});
    assert(response2_2.isOk());
    assert((FEN{handler2.getState()}.getRawString() == "8/4k3/8/8/8/8/4K3/8 w - - 0 1"));

    Handler handler3{FEN{"4kN2/8/8/8/8/8/8/4Kn2 w - - 0 0"}};
    Handler::Response response3_1 = handler3.move(Point{4, 7}, Point{5, 7});
    assert(response3_1.isOk());
    assert((FEN{handler3.getState()}.getRawString() == "4kN2/8/8/8/8/8/8/5K2 b - - 0 0"));
    Handler::Response response3_2 = handler3.move(Point{4, 0}, Point{5, 0});
    assert(response3_2.isOk());
    assert((FEN{handler3.getState()}.getRawString() == "5k2/8/8/8/8/8/8/5K2 w - - 0 1"));
}
