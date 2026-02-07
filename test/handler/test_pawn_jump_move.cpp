#include "test_handler.h"

void testPawnJumpMove() {
    Handler handler1{FEN{"4k3/7P/8/6P1/2nN4/bB3P2/PPPPP3/4K3 w - - 0 1"}};

    const Actions& whitePawnAActions = handler1.getActionsPlaces().getActions(Point{0, 6});
    assert(whitePawnAActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());

    const Actions& whitePawnBActions = handler1.getActionsPlaces().getActions(Point{1, 6});
    assert(whitePawnBActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());

    const Actions& whitePawnCActions = handler1.getActionsPlaces().getActions(Point{2, 6});
    assert_point_sets_are_equal(whitePawnCActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{2, 5}}));

    const Actions& whitePawnDActions = handler1.getActionsPlaces().getActions(Point{3, 6});
    assert_point_sets_are_equal(whitePawnDActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{3, 5}}));

    const Actions& whitePawnEActions = handler1.getActionsPlaces().getActions(Point{4, 6});
    assert_point_sets_are_equal(whitePawnEActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{4, 4}, {4, 5}}));

    const Actions& whitePawnFActions = handler1.getActionsPlaces().getActions(Point{5, 5});
    assert_point_sets_are_equal(whitePawnFActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{5, 4}}));

    const Actions& whitePawnGActions = handler1.getActionsPlaces().getActions(Point{6, 3});
    assert_point_sets_are_equal(whitePawnGActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{6, 2}}));

    const Actions& whitePawnHActions = handler1.getActionsPlaces().getActions(Point{7, 1});
    assert_point_sets_are_equal(whitePawnHActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{7, 0}}));

    Handler handler2{FEN{"4k3/ppppp3/Bb3p2/2Nn4/6p1/8/7p/4K3 b - - 0 1"}};

    const Actions& blackPawnAActions = handler2.getActionsPlaces().getActions(Point{0, 1});
    assert(blackPawnAActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());

    const Actions& blackPawnBActions = handler2.getActionsPlaces().getActions(Point{1, 1});
    assert(blackPawnBActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());

    const Actions& blackPawnCActions = handler2.getActionsPlaces().getActions(Point{2, 1});
    assert_point_sets_are_equal(blackPawnCActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{2, 2}}));

    const Actions& blackPawnDActions = handler2.getActionsPlaces().getActions(Point{3, 1});
    assert_point_sets_are_equal(blackPawnDActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{3, 2}}));

    const Actions& blackPawnEActions = handler2.getActionsPlaces().getActions(Point{4, 1});
    assert_point_sets_are_equal(blackPawnEActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{4, 2}, {4, 3}}));

    const Actions& blackPawnFActions = handler2.getActionsPlaces().getActions(Point{5, 2});
    assert_point_sets_are_equal(blackPawnFActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{5, 3}}));

    const Actions& blackPawnGActions = handler2.getActionsPlaces().getActions(Point{6, 4});
    assert_point_sets_are_equal(blackPawnGActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{6, 5}}));

    const Actions& blackPawnHActions = handler2.getActionsPlaces().getActions(Point{7, 6});
    assert_point_sets_are_equal(blackPawnHActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{7, 7}}));
}
