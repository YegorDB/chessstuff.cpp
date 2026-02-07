#include "test_handler.h"

void testPawnEnPassant() {
    Handler handler1{FEN{"4k3/8/8/8/6p1/8/7P/4K3 w - - 0 1"}};

    Handler::Response response1 = handler1.move(sp("h2"), sp("h4"));
    assert(response1.isOk());

    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "4k3/8/8/8/6pP/8/8/4K3 b - h3 0 1");

    const Actions& pawnGActions = handler1.getActionsPlaces().getActions(sp("g4"));
    assert_point_sets_are_equal(pawnGActions.get(Action::Type::THREAT).get(Action::Relation::TO), PointSet{sp("h3")});

    Handler::Response response2 = handler1.move(sp("g4"), sp("h3"));
    assert(response2.isOk());

    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "4k3/8/8/8/8/7p/8/4K3 w - - 0 2");

    Handler handler2{FEN{"4k3/p7/8/1P6/8/8/8/4K3 b - - 0 1"}};

    Handler::Response response3 = handler2.move(sp("a7"), sp("a5"));
    assert(response3.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "4k3/8/8/pP6/8/8/8/4K3 w - a6 0 2");

    const Actions& pawnBActions = handler2.getActionsPlaces().getActions(sp("b5"));
    assert_point_sets_are_equal(pawnBActions.get(Action::Type::THREAT).get(Action::Relation::TO), PointSet{sp("a6")});

    Handler::Response response4 = handler2.move(sp("b5"), sp("a6"));
    assert(response4.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "4k3/8/P7/8/8/8/8/4K3 b - - 0 2");
}
