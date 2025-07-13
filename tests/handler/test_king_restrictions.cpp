#include "test_handler.h"

void testKingRestrictions() {
    Handler handler1{FEN{"3rk3/3b4/8/8/8/3K4/3bp3/8 w - - 0 0"}};
    
    Actions kingSquareActions1 = handler1.getActionsPlaces().getActions(Point{3, 5});
    assert((kingSquareActions1.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, 4}, Point{3, 4}, Point{4, 4}, Point{2, 6}}));
    assert((kingSquareActions1.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{3, 6}, Point{4, 6}}));

    Handler handler2{FEN{"3rk3/8/8/5b2/8/3K4/3bp3/8 w - - 0 0"}};

    Actions kingSquareActions2 = handler2.getActionsPlaces().getActions(Point{3, 5});
    assert((kingSquareActions2.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, 4}}));
    assert((kingSquareActions2.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{4, 6}}));
}
