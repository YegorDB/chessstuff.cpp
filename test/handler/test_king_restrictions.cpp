#include "test_handler.h"

void testKingRestrictions() {
    Handler handler1{FEN{"3rk3/3b4/8/8/8/3K4/3bp3/8 w - - 0 1"}};

    ActionsPlaces ap1 = handler1.getActionsPlaces();
    assert_point_sets_are_equal(ap1.getActions(sp("d3")).get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{sp("c4"), sp("d4"), sp("e4"), sp("c2")}));
    assert_point_sets_are_equal(ap1.getActions(sp("d3")).get(Action::Type::THREAT).get(Action::Relation::TO), (PointSet{sp("d2"), sp("e2")}));
    assert(ap1.getActions(sp("c4")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("c4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("d4")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("d4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("e4")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("e4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap1.getActions(sp("c3")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d2")}));
    assert(ap1.getActions(sp("c3")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap1.getActions(sp("e3")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d2")}));
    assert(ap1.getActions(sp("e3")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("c2")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(ap1.getActions(sp("c2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap1.getActions(sp("d2")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d3")}));
    assert(ap1.getActions(sp("d2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap1.getActions(sp("e2")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d3")}));
    assert(ap1.getActions(sp("e2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());

    Handler handler2{FEN{"3rk3/8/8/5b2/8/3K4/3bp3/8 w - - 0 1"}};

    ActionsPlaces ap2 = handler2.getActionsPlaces();
    assert_point_sets_are_equal(ap2.getActions(sp("d3")).get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{sp("c4")}));
    assert_point_sets_are_equal(ap2.getActions(sp("d3")).get(Action::Type::THREAT).get(Action::Relation::TO), (PointSet{sp("e2")}));
    assert(ap2.getActions(sp("c4")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert(ap2.getActions(sp("c4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("d4")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d8")}));
    assert(ap2.getActions(sp("d4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("e4")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("f5")}));
    assert(ap2.getActions(sp("e4")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("c3")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d2")}));
    assert(ap2.getActions(sp("c3")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("e3")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d2")}));
    assert(ap2.getActions(sp("e3")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
    assert(ap2.getActions(sp("c2")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("c2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY), (PointSet{sp("f5")}));
    assert(ap2.getActions(sp("d2")).get(Action::Type::THREAT).get(Action::Relation::BY).empty());
    assert_point_sets_are_equal(ap2.getActions(sp("d2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY), (PointSet{sp("d8")}));
    assert_point_sets_are_equal(ap2.getActions(sp("e2")).get(Action::Type::THREAT).get(Action::Relation::BY), (PointSet{sp("d3")}));
    assert(ap2.getActions(sp("e2")).get(Action::Type::AFTER_KING_RESTRICTION).get(Action::Relation::BY).empty());
}
