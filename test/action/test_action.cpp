#include "test_action.h"

void testSingleAction() {
    Action action{};
    Square square1{"e3"};
    Square square2{"g7"};
    Square square3{"a5"};

    action.insert(Action::Relation::TO, square1.point);
    assert_point_sets_are_equal(action.get(Action::Relation::TO), PointSet{square1.point});

    action.insert(Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(action.get(Action::Relation::BY), PointSet{square2.point});

    action.insert(Action::Relation::BY, square3.point);
    assert_point_sets_are_equal(action.get(Action::Relation::BY), (PointSet{square2.point, square3.point}));

    action.erase(Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(action.get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(action.get(Action::Relation::BY), PointSet{square3.point});

    action.clear();

    assert(action.get(Action::Relation::TO).empty());
    assert(action.get(Action::Relation::BY).empty());
};

void testActions() {
    Actions actions{};
    Square square1{"b8"};
    Square square2{"h1"};

    actions.insert(Action::Type::THREAT, Action::Relation::TO, square1.point);
    actions.insert(Action::Type::THREAT, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::THREAT).get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(Action::Type::THREAT).get(Action::Relation::BY), PointSet{square2.point});

    actions.insert(Action::Type::SUPPORT, Action::Relation::TO, square1.point);
    actions.insert(Action::Type::SUPPORT, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::SUPPORT).get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(Action::Type::SUPPORT).get(Action::Relation::BY), PointSet{square2.point});

    actions.insert(Action::Type::PLACE, Action::Relation::TO, square1.point);
    actions.insert(Action::Type::PLACE, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::PLACE).get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(Action::Type::PLACE).get(Action::Relation::BY), PointSet{square2.point});

    actions.insert(Action::Type::XRAY, Action::Relation::TO, square1.point);
    actions.insert(Action::Type::XRAY, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::XRAY).get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(Action::Type::XRAY).get(Action::Relation::BY), PointSet{square2.point});

    actions.insert(Action::Type::BIND, Action::Relation::TO, square1.point);
    actions.insert(Action::Type::BIND, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::BIND).get(Action::Relation::TO), PointSet{square1.point});
    assert_point_sets_are_equal(actions.get(Action::Type::BIND).get(Action::Relation::BY), PointSet{square2.point});

    actions.erase(Action::Type::PLACE, Action::Relation::BY, square2.point);
    assert_point_sets_are_equal(actions.get(Action::Type::PLACE).get(Action::Relation::TO), PointSet{square1.point});
    assert(actions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());

    actions.clear();

    assert(actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(actions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(actions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(actions.get(Action::Type::BIND).get(Action::Relation::TO).empty());
    assert(actions.get(Action::Type::BIND).get(Action::Relation::BY).empty());
};

void testAction() {
    testSingleAction();
    testActions();
    testActionPlaces();

    std::cout << "testAction OK" << std::endl;
};
