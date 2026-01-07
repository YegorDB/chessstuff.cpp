#include "test_handler.h"

void testCastleMove() {
    Handler handler1{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Actions actions1 = handler1.getActionsPlaces().getActions(sp("e1"));
    assert_point_sets_are_equal(actions1.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c1"), sp("d1"), sp("d2"), sp("e2"), sp("f2"), sp("f1"), sp("g1")}));

    Handler::Response response1 = handler1.move(sp("e1"), sp("g1"));
    assert(response1.isOk());

    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "r3k2r/8/8/8/8/8/8/R4RK1 b kq - 1 1");

    Handler handler2{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Handler::Response response2 = handler2.move(sp("e1"), sp("c1"));
    assert(response2.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "r3k2r/8/8/8/8/8/8/2KR3R b kq - 1 1");

    Handler handler3{FEN{"r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"}};

    Actions actions2 = handler3.getActionsPlaces().getActions(sp("e8"));
    assert_point_sets_are_equal(actions2.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c8"), sp("d8"), sp("d7"), sp("e7"), sp("f7"), sp("f8"), sp("g8")}));

    Handler::Response response3 = handler3.move(sp("e8"), sp("g8"));
    assert(response3.isOk());

    assert_strings_are_equal(FEN{handler3.getState()}.getRawString(), "r4rk1/8/8/8/8/8/8/R3K2R w KQ - 1 2");

    Handler handler4{FEN{"r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"}};

    Handler::Response response4 = handler4.move(sp("e8"), sp("c8"));
    assert(response4.isOk());

    assert_strings_are_equal(FEN{handler4.getState()}.getRawString(), "2kr3r/8/8/8/8/8/8/R3K2R w KQ - 1 2");
}

void testRestrictCastleMove() {
    Handler handler1{FEN{"r3k2r/4q3/8/8/8/8/8/R3K2R w KQkq - 0 1"}};
    Actions actions1 = handler1.getActionsPlaces().getActions(sp("e1"));
    assert_point_sets_are_equal(actions1.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d1"), sp("d2"), sp("f2"), sp("f1")}));

    Handler handler2{FEN{"r3k2r/8/8/8/8/8/4b3/R3K2R w KQkq - 0 1"}};
    Actions actions2 = handler2.getActionsPlaces().getActions(sp("e1"));
    assert_point_sets_are_equal(actions2.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d2"), sp("f2")}));

    Handler handler3{FEN{"r3k2r/8/8/8/8/4b3/8/R3K2R w KQkq - 0 1"}};
    Actions actions3 = handler3.getActionsPlaces().getActions(sp("e1"));
    assert_point_sets_are_equal(actions3.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d1"), sp("e2"), sp("f1")}));

    Handler handler4{FEN{"r3k2r/8/8/8/4b3/8/8/R3K2R w KQkq - 0 1"}};
    Actions actions4 = handler4.getActionsPlaces().getActions(sp("e1"));
    assert_point_sets_are_equal(actions4.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c1"), sp("d1"), sp("d2"), sp("e2"), sp("f2"), sp("f1"), sp("g1")}));

    Handler handler5{FEN{"r3k2r/8/8/8/8/8/4Q3/R3K2R b KQkq - 0 1"}};
    Actions actions5 = handler5.getActionsPlaces().getActions(sp("e8"));
    assert_point_sets_are_equal(actions5.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d8"), sp("d7"), sp("f7"), sp("f8")}));

    Handler handler6{FEN{"r3k2r/4B3/8/8/8/8/8/R3K2R b KQkq - 0 1"}};
    Actions actions6 = handler6.getActionsPlaces().getActions(sp("e8"));
    assert_point_sets_are_equal(actions6.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d7"), sp("f7")}));

    Handler handler7{FEN{"r3k2r/8/4B3/8/8/8/8/R3K2R b KQkq - 0 1"}};
    Actions actions7 = handler7.getActionsPlaces().getActions(sp("e8"));
    assert_point_sets_are_equal(actions7.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("d8"), sp("e7"), sp("f8")}));

    Handler handler8{FEN{"r3k2r/8/8/4B3/8/8/8/R3K2R b KQkq - 0 1"}};
    Actions actions8 = handler8.getActionsPlaces().getActions(sp("e8"));
    assert_point_sets_are_equal(actions8.get(ActionType::PLACE).get(ActionRelation::TO), (PointSet{sp("c8"), sp("d8"), sp("d7"), sp("e7"), sp("f7"), sp("f8"), sp("g8")}));
}

void testCastleDrop() {
    Handler handler1{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Handler::Response response1 = handler1.move(sp("e1"), sp("e2"));
    assert(response1.isOk());

    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "r3k2r/8/8/8/8/8/4K3/R6R b kq - 1 1");

    Handler::Response response2 = handler1.move(sp("e8"), sp("e7"));
    assert(response2.isOk());

    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "r6r/4k3/8/8/8/8/4K3/R6R w - - 2 2");

    Handler handler2{FEN{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"}};

    Handler::Response response3 = handler2.move(sp("h1"), sp("g1"));
    assert(response3.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "r3k2r/8/8/8/8/8/8/R3K1R1 b Qkq - 1 1");

    Handler::Response response4 = handler2.move(sp("h8"), sp("f8"));
    assert(response4.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "r3kr2/8/8/8/8/8/8/R3K1R1 w Qq - 2 2");

    Handler::Response response5 = handler2.move(sp("a1"), sp("b1"));
    assert(response5.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "r3kr2/8/8/8/8/8/8/1R2K1R1 b q - 3 2");

    Handler::Response response6 = handler2.move(sp("a8"), sp("c8"));
    assert(response6.isOk());

    assert_strings_are_equal(FEN{handler2.getState()}.getRawString(), "2r1kr2/8/8/8/8/8/8/1R2K1R1 w - - 4 3");
}

void testCastleOneSide() {
    Handler handler1{FEN{"4k2r/8/8/8/8/8/8/R3K3 w Qk - 0 1"}};

    Handler::Response response1 = handler1.move(sp("e1"), sp("c1"));
    assert(response1.isOk());
    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "4k2r/8/8/8/8/8/8/2KR4 b k - 1 1");

    Handler::Response response2 = handler1.move(sp("e8"), sp("g8"));
    assert(response2.isOk());
    assert_strings_are_equal(FEN{handler1.getState()}.getRawString(), "5rk1/8/8/8/8/8/8/2KR4 w - - 2 2");
}

void testCastleThrowErrors() {
    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/R2KN2R w KQ - 0 1"}};
        },
        "Wrong king piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4K3/8/8/8/8/8/8/R2NkN1R w KQ - 0 1"}};
        },
        "Wrong king piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/N3K2R w KQ - 0 1"}};
        },
        "Wrong rook piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/R3K2N w KQ - 0 1"}};
        },
        "Wrong rook piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/N3K2R w KQ - 0 1"}};
        },
        "Wrong rook piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/r2NK2R w KQ - 0 1"}};
        },
        "Wrong rook piece to castle."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/R3KN1r w KQ - 0 1"}};
        },
        "Wrong rook piece to castle."
    );
}

void testCastle() {
    testCastleMove();
    testRestrictCastleMove();
    testCastleDrop();
    testCastleOneSide();
    testCastleThrowErrors();
}
