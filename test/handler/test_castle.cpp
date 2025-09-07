#include "test_handler.h"

void testCastleDrop() {
    Handler handler1{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Handler::Response response1 = handler1.move(sp("e1"), sp("e2"));
    assert(response1.isOk());

    assert((FEN{handler1.getState()}.getRawString() == "r3k2r/8/8/8/8/8/4K3/R6R b kq - 0 1"));

    Handler::Response response2 = handler1.move(sp("e8"), sp("e7"));
    assert(response2.isOk());

    assert((FEN{handler1.getState()}.getRawString() == "r6r/4k3/8/8/8/8/4K3/R6R w - - 0 2"));

    Handler handler2{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Handler::Response response3 = handler2.move(sp("h1"), sp("g1"));
    assert(response3.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 0 1"));

    Handler::Response response4 = handler2.move(sp("h8"), sp("f8"));
    assert(response4.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "r3kr2/8/8/8/8/8/8/R3K1R1 w Qq - 0 2"));

    Handler::Response response5 = handler2.move(sp("a1"), sp("b1"));
    assert(response5.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "r3kr2/8/8/8/8/8/8/1R2K1R1 b q - 0 2"));

    Handler::Response response6 = handler2.move(sp("a8"), sp("c8"));
    assert(response6.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "2r1kr2/8/8/8/8/8/8/1R2K1R1 w - - 0 3"));
}

void testCastle() {
    testCastleDrop();
}