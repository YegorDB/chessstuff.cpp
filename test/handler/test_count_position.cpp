#include "test_handler.h"

void testCountPosition() {
    Handler handler{FEN{"3qk3/8/8/8/8/8/8/3QK3 w - - 0 1"}};

    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getPositionCounts().at("3qk3/8/8/8/8/8/8/3QK3 w - -") == 1);

    Handler::Response response1 = handler.move(sp("e1"), sp("e2"));
    assert(response1.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getPositionCounts().contains("3qk3/8/8/8/8/8/4K3/3Q4 b - -"));
    assert(handler.getPositionCounts().at("3qk3/8/8/8/8/8/4K3/3Q4 b - -") == 1);

    Handler::Response response2 = handler.move(sp("e8"), sp("e7"));
    assert(response2.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getPositionCounts().contains("3q4/4k3/8/8/8/8/4K3/3Q4 w - -"));
    assert(handler.getPositionCounts().at("3q4/4k3/8/8/8/8/4K3/3Q4 w - -") == 1);

    Handler::Response response3 = handler.move(sp("e2"), sp("e1"));
    assert(response3.isOk());
    assert(handler.getMaxPositionCount() == 1);
    assert(handler.getPositionCounts().contains("3q4/4k3/8/8/8/8/8/3QK3 b - -"));
    assert(handler.getPositionCounts().at("3q4/4k3/8/8/8/8/8/3QK3 b - -") == 1);

    Handler::Response response4 = handler.move(sp("e7"), sp("e8"));
    assert(response4.isOk());
    assert(handler.getMaxPositionCount() == 2);
    assert(handler.getPositionCounts().contains("3qk3/8/8/8/8/8/8/3QK3 w - -"));
    assert(handler.getPositionCounts().at("3qk3/8/8/8/8/8/8/3QK3 w - -") == 2);
}
