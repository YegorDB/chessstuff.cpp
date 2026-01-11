#include "test_action.h"

void testSingleAction() {
    Action action{};
    Square square1{"e3"};
    Square square2{"g7"};
    Square square3{"a5"};

    action.insert(ActionRelation::TO, square1.point);
    assert_point_sets_are_equal(action.get(ActionRelation::TO), PointSet{square1.point});

    action.insert(ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(action.get(ActionRelation::BY), PointSet{square2.point});

    action.insert(ActionRelation::BY, square3.point);
    assert_point_sets_are_equal(action.get(ActionRelation::BY), (PointSet{square2.point, square3.point}));

    action.erase(ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(action.get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(action.get(ActionRelation::BY), PointSet{square3.point});

    action.clear();

    assert(action.get(ActionRelation::TO).empty());
    assert(action.get(ActionRelation::BY).empty());
};

void testActions() {
    Actions actions{};
    Square square1{"b8"};
    Square square2{"h1"};

    actions.insert(ActionType::THREAT, ActionRelation::TO, square1.point);
    actions.insert(ActionType::THREAT, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::THREAT).get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(ActionType::THREAT).get(ActionRelation::BY), PointSet{square2.point});

    actions.insert(ActionType::SUPPORT, ActionRelation::TO, square1.point);
    actions.insert(ActionType::SUPPORT, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::SUPPORT).get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(ActionType::SUPPORT).get(ActionRelation::BY), PointSet{square2.point});

    actions.insert(ActionType::PLACE, ActionRelation::TO, square1.point);
    actions.insert(ActionType::PLACE, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(ActionType::PLACE).get(ActionRelation::BY), PointSet{square2.point});

    actions.insert(ActionType::XRAY, ActionRelation::TO, square1.point);
    actions.insert(ActionType::XRAY, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::XRAY).get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(ActionType::XRAY).get(ActionRelation::BY), PointSet{square2.point});

    actions.insert(ActionType::BIND, ActionRelation::TO, square1.point);
    actions.insert(ActionType::BIND, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::BIND).get(ActionRelation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(ActionType::BIND).get(ActionRelation::BY), PointSet{square2.point});

    actions.erase(ActionType::PLACE, ActionRelation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(ActionType::PLACE).get(ActionRelation::TO), PointSet{square1.point});
    assert(actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());

    actions.clear();

    assert(actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::BIND).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::BIND).get(ActionRelation::BY).empty());
};

void testAction() {
    testSingleAction();
    testActions();
    testActionPlaces();

    std::cout << "testAction OK" << std::endl;
};
