#include "test_action.h"

void testSingleAction() {
    Action action{};
    Square square1{"e3"};
    Square square2{"g7"};

    action.insert(ActionRelation::TO, square1.point);

    PointSet toPoints = action.get(ActionRelation::TO);
    assert(toPoints.size() == 1);
    assert(toPoints.find(square1.point) != toPoints.end());

    action.insert(ActionRelation::BY, square2.point);

    PointSet byPoints = action.get(ActionRelation::BY);
    assert(byPoints.size() == 1);
    assert(byPoints.find(square2.point) != byPoints.end());

    action.clear();

    assert(action.get(ActionRelation::TO).empty());
    assert(action.get(ActionRelation::BY).empty());
};

void testActions() {
    Actions actions{};
    Square square1{"b8"};
    Square square2{"h1"};

    actions.insert(ActionType::THREAT, ActionRelation::BY, square1.point);
    actions.insert(ActionType::THREAT, ActionRelation::TO, square2.point);
    assert(!actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    actions.insert(ActionType::SUPPORT, ActionRelation::TO, square1.point);
    actions.insert(ActionType::SUPPORT, ActionRelation::BY, square2.point);
    assert(!actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());

    actions.insert(ActionType::PLACE, ActionRelation::TO, square1.point);
    actions.insert(ActionType::PLACE, ActionRelation::BY, square2.point);
    assert(!actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());

    actions.insert(ActionType::XRAY, ActionRelation::TO, square1.point);
    actions.insert(ActionType::XRAY, ActionRelation::BY, square2.point);
    assert(!actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    actions.clear();

    assert(actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
};

void testAction() {
    testSingleAction();
    testActions();

    std::cout << "testAction OK" << std::endl;
};
