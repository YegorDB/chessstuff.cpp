#include "test_action.h"

void testActionPlaces() {
    ActionsPlaces actionsPlaces{};

    assert(actionsPlaces.getItems().size() == 64);

    Point byPoint{1, 1};
    Point toPoint1{2, 2};
    Point toPoint2{3, 3};
    Point toPoint3{4, 4};
    Point wrongPoint;
    ActionType actionType = ActionType::PLACE;

    actionsPlaces.setAction(actionType, byPoint, toPoint1);
    actionsPlaces.setAction(actionType, byPoint, toPoint2);
    actionsPlaces.setAction(actionType, byPoint, toPoint3);
    assert_point_sets_are_equal(actionsPlaces.getActions(byPoint).get(actionType).get(ActionRelation::TO), (PointSet{toPoint1, toPoint2, toPoint3}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint1).get(actionType).get(ActionRelation::BY), (PointSet{byPoint}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint2).get(actionType).get(ActionRelation::BY), (PointSet{byPoint}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint3).get(actionType).get(ActionRelation::BY), (PointSet{byPoint}));

    actionsPlaces.erasePoints(byPoint, actionType, PointSet{toPoint1, toPoint2});
    assert_point_sets_are_equal(actionsPlaces.getActions(byPoint).get(actionType).get(ActionRelation::TO), (PointSet{toPoint3}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint1).get(actionType).get(ActionRelation::BY), (PointSet{}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint2).get(actionType).get(ActionRelation::BY), (PointSet{}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint3).get(actionType).get(ActionRelation::BY), (PointSet{byPoint}));

    actionsPlaces.clearActions();
    assert_point_sets_are_equal(actionsPlaces.getActions(byPoint).get(actionType).get(ActionRelation::TO), (PointSet{}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint1).get(actionType).get(ActionRelation::BY), (PointSet{}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint2).get(actionType).get(ActionRelation::BY), (PointSet{}));
    assert_point_sets_are_equal(actionsPlaces.getActions(toPoint3).get(actionType).get(ActionRelation::BY), (PointSet{}));

    assert_error_was_thrown(
        [&](){
            actionsPlaces.setAction(actionType, wrongPoint, toPoint1);
        },
        "Wrong point."
    );

    assert_error_was_thrown(
        [&](){
            actionsPlaces.setAction(actionType, byPoint, wrongPoint);
        },
        "Wrong point."
    );
};
