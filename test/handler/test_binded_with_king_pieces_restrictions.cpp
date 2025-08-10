#include "test_handler.h"

void testBindedWithKingPiecesRestrictions() {
    Handler handler{FEN{"8/8/3k4/2r5/1B1q1n2/1K6/3R3Q/8 b - - 0 0"}};

    Actions blackRookActions = handler.getActionsPlaces().getActions(Point{2, 3});
    PointSet expectedBlackRookPlaceTo;
    assert_point_sets_are_equal(blackRookActions.get(ActionType::PLACE).get(ActionRelation::TO), expectedBlackRookPlaceTo);
    PointSet expectedBlackRookThreatTo;
    assert_point_sets_are_equal(blackRookActions.get(ActionType::THREAT).get(ActionRelation::TO), expectedBlackRookThreatTo);

    Actions blackQueenActions = handler.getActionsPlaces().getActions(Point{3, 4});
    PointSet expectedBlackQueenPlaceTo{Point{3, 3}, Point{3, 5}};
    assert_point_sets_are_equal(blackQueenActions.get(ActionType::PLACE).get(ActionRelation::TO), expectedBlackQueenPlaceTo);
    PointSet expectedBlackQueenThreatTo{Point{3, 6}};
    assert_point_sets_are_equal(blackQueenActions.get(ActionType::THREAT).get(ActionRelation::TO), expectedBlackQueenThreatTo);

    Actions blackKnightActions = handler.getActionsPlaces().getActions(Point{5, 4});
    PointSet expectedBlackKnightPlaceTo;
    assert_point_sets_are_equal(blackKnightActions.get(ActionType::PLACE).get(ActionRelation::TO), expectedBlackKnightPlaceTo);
    PointSet expectedBlackKnightThreatTo;
    assert_point_sets_are_equal(blackKnightActions.get(ActionType::THREAT).get(ActionRelation::TO), expectedBlackKnightThreatTo);
}
