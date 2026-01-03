#include "test_handler.h"

void testHandlerHistoryMoves() {
    Handler handler{FEN{"r3k3/ppp3P1/8/3n1R2/8/7B/4P3/4K2R w Kq - 0 1"}};

    assert_strings_are_equal(handler.getHistoryMoves().toString(), "");

    Handler::Response response1 = handler.move(sp("e2"), sp("e4"));
    assert(response1.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "r3k3/ppp3P1/8/3n1R2/4P3/7B/8/4K2R b Kq e3 0 1");

    Handler::Response response2 = handler.move(sp("d5"), sp("e7"));
    assert(response2.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "r3k3/ppp1n1P1/8/5R2/4P3/7B/8/4K2R w Kq - 1 2");

    Handler::Response response3 = handler.move(sp("e1"), sp("g1"));
    assert(response3.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "r3k3/ppp1n1P1/8/5R2/4P3/7B/8/5RK1 b q - 2 2");

    Handler::Response response4 = handler.move(sp("e8"), sp("c8"));
    assert(response4.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "2kr4/ppp1n1P1/8/5R2/4P3/7B/8/5RK1 w - - 3 3");

    Handler::Response response5 = handler.move(sp("g7"), sp("g8"));
    assert(response5.isOk());
    Handler::Response response6 = handler.promotePawn(PieceType::QUEEN);
    assert(response6.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0 3.g8=Q");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "2kr2Q1/ppp1n3/8/5R2/4P3/7B/8/5RK1 b - - 0 3");

    Handler::Response response7 = handler.move(sp("e7"), sp("g8"));
    assert(response7.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0 3.g8=Q Nxg8");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "2kr2n1/ppp5/8/5R2/4P3/7B/8/5RK1 w - - 0 4");

    Handler::Response response8 = handler.move(sp("f5"), sp("f8"));
    assert(response8.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0 3.g8=Q Nxg8 4.Rf8+");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "2kr1Rn1/ppp5/8/8/4P3/7B/8/5RK1 b - - 1 4");

    Handler::Response response9 = handler.move(sp("c8"), sp("b8"));
    assert(response9.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0 3.g8=Q Nxg8 4.Rf8+ Kb8");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "1k1r1Rn1/ppp5/8/8/4P3/7B/8/5RK1 w - - 2 5");

    Handler::Response response10 = handler.move(sp("f8"), sp("d8"));
    assert(response10.isOk());
    assert_strings_are_equal(handler.getHistoryMoves().toString(), "1.e4 Ne7 2.0-0 0-0-0 3.g8=Q Nxg8 4.Rf8+ Kb8 5.Rxd8#");
    assert_strings_are_equal(FEN{handler.getState()}.getRawString(), "1k1R2n1/ppp5/8/8/4P3/7B/8/5RK1 b - - 0 5");
}
