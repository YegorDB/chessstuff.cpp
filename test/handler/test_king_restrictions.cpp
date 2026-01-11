#include "test_handler.h"

void testKingRestrictions() {
    Handler handler1{FEN{"3rk3/3b4/8/8/8/3K4/3bp3/8 w - - 0 1"}};
    
    Actions actions1 = handler1.getActionsPlaces().getActions(sp("d3"));
    assert_point_sets_are_equal(actions1.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c4"), sp("d4"), sp("e4"), sp("c2")}));
    assert_point_sets_are_equal(actions1.get(ActionType::THREAT).get(ActionRelation::TO), (PointSet{sp("d2"), sp("e2")}));

    Handler handler2{FEN{"3rk3/8/8/5b2/8/3K4/3bp3/8 w - - 0 1"}};

    Actions actions2 = handler2.getActionsPlaces().getActions(sp("d3"));
    assert_point_sets_are_equal(actions2.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c4")}));
    assert_point_sets_are_equal(actions2.get(ActionType::THREAT).get(ActionRelation::TO), (PointSet{sp("e2")}));
}
