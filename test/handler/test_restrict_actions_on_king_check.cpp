#include "test_handler.h"

void testRestrictActionsOnKingCheck() {
    Handler handler1{FEN{"8/8/3nk3/8/B3K3/2Q1N3/3R3P/8 w - - 0 0"}};

    Actions bishopActions1 = handler1.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions1.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopActions1.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions queenActions1 = handler1.getActionsPlaces().getActions(sp("c3"));
    assert(queenActions1.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(queenActions1.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions rookActions1 = handler1.getActionsPlaces().getActions(sp("d2"));
    assert(rookActions1.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(rookActions1.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("d6")});

    Actions knightActions1 = handler1.getActionsPlaces().getActions(sp("e3"));
    assert(knightActions1.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(knightActions1.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions pawnActions1 = handler1.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions1.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions1.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Handler handler2{FEN{"8/8/4k3/3p4/B3K3/2Q1N3/3R3P/8 w - - 0 0"}};

    Actions bishopActions2 = handler2.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions2.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopActions2.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions queenActions2 = handler2.getActionsPlaces().getActions(sp("c3"));
    assert(queenActions2.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(queenActions2.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions rookActions2 = handler2.getActionsPlaces().getActions(sp("d2"));
    assert(rookActions2.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(rookActions2.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("d5")});

    Actions knightActions2 = handler2.getActionsPlaces().getActions(sp("e3"));
    assert(knightActions2.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(knightActions2.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("d5")});

    Actions pawnActions2 = handler2.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions2.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions2.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Handler handler3{FEN{"8/8/2b1k3/8/B3K3/2Q1N3/3R3P/8 w - - 0 0"}};

    Actions bishopActions3 = handler3.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions3.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(bishopActions3.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c6")});

    Actions queenActions3 = handler3.getActionsPlaces().getActions(sp("c3"));
    assert(queenActions3.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(queenActions3.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c6")});

    Actions rookActions3 = handler3.getActionsPlaces().getActions(sp("d2"));
    assert_point_sets_are_equal(rookActions3.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("d5")});
    assert(rookActions3.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions knightActions3 = handler3.getActionsPlaces().getActions(sp("e3"));
    assert_point_sets_are_equal(knightActions3.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("d5")});
    assert(knightActions3.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions pawnActions3 = handler3.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions3.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions3.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Handler handler4{FEN{"8/8/4k3/8/Br2K3/2Q1N3/3R3P/8 w - - 0 0"}};

    Actions bishopActions4 = handler4.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions4.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopActions4.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions queenActions4 = handler4.getActionsPlaces().getActions(sp("c3"));
    assert_point_sets_are_equal(queenActions4.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c4"), sp("d4")}));
    assert_point_sets_are_equal(queenActions4.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("b4")});

    Actions rookActions4 = handler4.getActionsPlaces().getActions(sp("d2"));
    assert_point_sets_are_equal(rookActions4.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("d4")});
    assert(rookActions4.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions knightActions4 = handler4.getActionsPlaces().getActions(sp("e3"));
    assert_point_sets_are_equal(knightActions4.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("c4")});
    assert(knightActions4.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions pawnActions4 = handler4.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions4.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions4.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Handler handler5{FEN{"8/8/4k3/8/B3K3/2Q1N3/2qR3P/8 w - - 0 0"}};

    Actions bishopActions5 = handler5.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions5.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(bishopActions5.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c2")});

    Actions queenActions5 = handler5.getActionsPlaces().getActions(sp("c3"));
    assert_point_sets_are_equal(queenActions5.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("d3")});
    assert_point_sets_are_equal(queenActions5.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c2")});

    Actions rookActions5 = handler5.getActionsPlaces().getActions(sp("d2"));
    assert_point_sets_are_equal(rookActions5.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{sp("d3")});
    assert_point_sets_are_equal(rookActions5.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c2")});

    Actions knightActions5 = handler5.getActionsPlaces().getActions(sp("e3"));
    assert(knightActions5.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert_point_sets_are_equal(knightActions5.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{sp("c2")});

    Actions pawnActions5 = handler5.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions5.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions5.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Handler handler6{FEN{"8/7b/4k3/8/B3K1r1/2Q1N3/3R3P/8 w - - 0 0"}};

    Actions bishopActions6 = handler6.getActionsPlaces().getActions(sp("a4"));
    assert(bishopActions6.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopActions6.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions queenActions6 = handler6.getActionsPlaces().getActions(sp("c3"));
    assert(queenActions6.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(queenActions6.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions rookActions6 = handler6.getActionsPlaces().getActions(sp("d2"));
    assert(rookActions6.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(rookActions6.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions knightActions6 = handler6.getActionsPlaces().getActions(sp("e3"));
    assert(knightActions6.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(knightActions6.get(ActionType::THREAT).get(ActionRelation::TO).empty());

    Actions pawnActions6 = handler6.getActionsPlaces().getActions(sp("h2"));
    assert(pawnActions6.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(pawnActions6.get(ActionType::THREAT).get(ActionRelation::TO).empty());
}
