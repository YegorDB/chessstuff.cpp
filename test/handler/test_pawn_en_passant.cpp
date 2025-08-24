#include "test_handler.h"

void testPawnEnPassant() {
    Handler handler1{FEN{"4k3/8/8/8/6p1/8/7P/4K3 w - - 0 1"}};

    Handler::Response response1 = handler1.move(Square("h2").point, Square("h4").point);
    assert(response1.isOk());
    
    assert((FEN{handler1.getState()}.getRawString() == "4k3/8/8/8/6pP/8/8/4K3 b - h3 0 1"));
    
    const Actions& pawnGActions = handler1.getActionsPlaces().getActions(Square("g4").point);
    assert_point_sets_are_equal(pawnGActions.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{Square("h3").point});
    
    Handler::Response response2 = handler1.move(Square("g4").point, Square("h3").point);
    assert(response2.isOk());

    assert((FEN{handler1.getState()}.getRawString() == "4k3/8/8/8/8/7p/8/4K3 w - - 0 2"));

    Handler handler2{FEN{"4k3/p7/8/1P6/8/8/8/4K3 b - - 0 1"}};

    Handler::Response response3 = handler2.move(Square("a7").point, Square("a5").point);
    assert(response3.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "4k3/8/8/pP6/8/8/8/4K3 w - a6 0 2"));

    const Actions& pawnBActions = handler2.getActionsPlaces().getActions(Square("b5").point);
    assert_point_sets_are_equal(pawnBActions.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{Square("a6").point});

    Handler::Response response4 = handler2.move(Square("b5").point, Square("a6").point);
    assert(response4.isOk());

    assert((FEN{handler2.getState()}.getRawString() == "4k3/8/P7/8/8/8/8/4K3 b - - 0 2"));
}
