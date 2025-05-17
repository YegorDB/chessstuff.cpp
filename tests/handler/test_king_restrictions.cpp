#include "test_handler.h"

void testKingRestrictions() {
    Handler handler{FEN{"3rk3/8/8/5b2/8/3K4/3bp3/8 w - - 0 0"}};
    
    Actions kingSquareActions = handler.getBoard().getSquare(Point{3, 5}).getActions();
    assert((kingSquareActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, 4}}));
    assert((kingSquareActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{4, 6}}));
}
