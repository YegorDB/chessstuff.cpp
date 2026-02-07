#include "test_handler.h"

void testInitialActions() {
    Handler handler{};
    const ActionsPlaces& actionsPlaces = handler.getActionsPlaces();

    for (auto [point, actions] : actionsPlaces.getItems()) {
        assert(actions.get(Action::Type::BIND).get(Action::Relation::TO).empty());
        assert(actions.get(Action::Type::BIND).get(Action::Relation::BY).empty());
    }

    for (int y : {0, 1, 2}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
            assert(actions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
        }
    }

    for (int y : {3, 4}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
            if (y == 3) {
                assert(actions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
            } else {
                assert_point_sets_are_equal(actions.get(Action::Type::PLACE).get(Action::Relation::BY), (PointSet{{x, 6}}));
            }
            assert(actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
            assert(actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
            assert(actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
            assert(actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
        }
    }

    for (int y : {5, 6, 7}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
            assert(actions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());
        }
    }

    const Actions& rookABActions = actionsPlaces.getActions(Point{0, 0});
    assert((rookABActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{1, 0}, Point{0, 1}}));
    assert(rookABActions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert((rookABActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{2, 0}, Point{0, 6}}));
    assert(rookABActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(rookABActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(rookABActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& knightBBActions = actionsPlaces.getActions(Point{1, 0});
    assert((knightBBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{3, 1}}));
    assert((knightBBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{0, 0}}));
    assert(knightBBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((knightBBActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 0}}));
    assert((knightBBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(knightBBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& bishopCBActions = actionsPlaces.getActions(Point{2, 0});
    assert((bishopCBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{1, 1}, Point{3, 1}}));
    assert((bishopCBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 0}}));
    assert(bishopCBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((bishopCBActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{0, 0}}));
    assert(bishopCBActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(bishopCBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& queenBActions = actionsPlaces.getActions(Point{3, 0});
    assert((queenBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{2, 0}, Point{4, 0}, Point{2, 1}, Point{3, 1}, Point{4, 1}}));
    assert((queenBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{4, 0}}));
    assert((queenBActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{1, 0}, Point{5, 0}, Point{3, 6}}));
    assert(queenBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(queenBActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(queenBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& kingBActions = actionsPlaces.getActions(Point{4, 0});
    assert((kingBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{3, 0}, Point{5, 0}, Point{3, 1}, Point{4, 1}, Point{5, 1}}));
    assert((kingBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 0}}));
    assert(kingBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(kingBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(kingBActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(kingBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& bishopFBActions = actionsPlaces.getActions(Point{5, 0});
    assert((bishopFBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{4, 1}, Point{6, 1}}));
    assert((bishopFBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{4, 0}}));
    assert(bishopFBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((bishopFBActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 0}, Point{7, 0}}));
    assert(bishopFBActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(bishopFBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& knightGBActions = actionsPlaces.getActions(Point{6, 0});
    assert((knightGBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{4, 1}}));
    assert((knightGBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{7, 0}}));
    assert(knightGBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(knightGBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((knightGBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(knightGBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& rookHBActions = actionsPlaces.getActions(Point{7, 0});
    assert((rookHBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{6, 0}, Point{7, 1}}));
    assert(rookHBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert((rookHBActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{5, 0}, Point{7, 6}}));
    assert(rookHBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(rookHBActions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert(rookHBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnABActions = actionsPlaces.getActions(Point{0, 1});
    assert(pawnABActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnABActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{0, 0}}));
    assert(pawnABActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnABActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{0, 7}}));
    assert((pawnABActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{1, 2}}));
    assert(pawnABActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnBBActions = actionsPlaces.getActions(Point{1, 1});
    assert(pawnBBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnBBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{2, 0}}));
    assert(pawnBBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnBBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((pawnBBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(pawnBBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnCBActions = actionsPlaces.getActions(Point{2, 1});
    assert(pawnCBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnCBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 0}}));
    assert(pawnCBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnCBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((pawnCBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{1, 2}, Point{3, 2}}));
    assert(pawnCBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnDBActions = actionsPlaces.getActions(Point{3, 1});
    assert(pawnDBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnDBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{1, 0}, Point{2, 0}, Point{3, 0}, Point{4, 0}}));
    assert(pawnDBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnDBActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 7}}));
    assert((pawnDBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{2, 2}, Point{4, 2}}));
    assert(pawnDBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnEBActions = actionsPlaces.getActions(Point{4, 1});
    assert(pawnEBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnEBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 0}, Point{4, 0}, Point{5, 0}, Point{6, 0}}));
    assert(pawnEBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnEBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((pawnEBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{3, 2}, Point{5, 2}}));
    assert(pawnEBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnFBActions = actionsPlaces.getActions(Point{5, 1});
    assert(pawnFBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnFBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{4, 0}}));
    assert(pawnFBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnFBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((pawnFBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{4, 2}, Point{6, 2}}));
    assert(pawnFBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnGBActions = actionsPlaces.getActions(Point{6, 1});
    assert(pawnGBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnGBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{5, 0}}));
    assert(pawnGBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnGBActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert((pawnGBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(pawnGBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& pawnHBActions = actionsPlaces.getActions(Point{7, 1});
    assert(pawnHBActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnHBActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{7, 0}}));
    assert(pawnHBActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnHBActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{7, 7}}));
    assert((pawnHBActions.get(Action::Type::THREAT).get(Action::Relation::TO) == PointSet{Point{6, 2}}));
    assert(pawnHBActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty());

    const Actions& squareA6Actions = actionsPlaces.getActions(Point{0, 2});
    assert(squareA6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareA6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareA6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareA6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareA6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareA6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{1, 0}, Point{1, 1}}));

    const Actions& squareB6Actions = actionsPlaces.getActions(Point{1, 2});
    assert(squareB6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareB6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareB6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareB6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareB6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareB6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{0, 1}, Point{2, 1}}));

    const Actions& squareC6Actions = actionsPlaces.getActions(Point{2, 2});
    assert(squareC6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareC6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareC6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareC6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareC6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareC6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{1, 0}, Point{1, 1}, Point{3, 1}}));

    const Actions& squareD6Actions = actionsPlaces.getActions(Point{3, 2});
    assert(squareD6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareD6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareD6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareD6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareD6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareD6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{2, 1}, Point{4, 1}}));

    const Actions& squareE6Actions = actionsPlaces.getActions(Point{4, 2});
    assert(squareE6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareE6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareE6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareE6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareE6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareE6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{3, 1}, Point{5, 1}}));

    const Actions& squareF6Actions = actionsPlaces.getActions(Point{5, 2});
    assert(squareF6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareF6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareF6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareF6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareF6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareF6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{6, 0}, Point{4, 1}, Point{6, 1}}));

    const Actions& squareG6Actions = actionsPlaces.getActions(Point{6, 2});
    assert(squareG6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareG6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareG6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareG6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareG6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareG6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{5, 1}, Point{7, 1}}));

    const Actions& squareH6Actions = actionsPlaces.getActions(Point{7, 2});
    assert(squareH6Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareH6Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareH6Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareH6Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
    assert(squareH6Actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty());
    assert((squareH6Actions.get(Action::Type::THREAT).get(Action::Relation::BY) == PointSet{Point{6, 0}, Point{6, 1}}));

    const Actions& rookAWActions = actionsPlaces.getActions(Point{0, 7});
    assert(rookAWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(rookAWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((rookAWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{1, 7}, Point{0, 6}}));
    assert(rookAWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert((rookAWActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{2, 7}, Point{0, 1}}));
    assert(rookAWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& knightBWActions = actionsPlaces.getActions(Point{1, 7});
    assert((knightBWActions.get(Action::Type::PLACE).get(Action::Relation::TO) == PointSet{Point{0, 5}, Point{2, 5}}));
    assert(knightBWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((knightBWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{3, 6}}));
    assert((knightBWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{0, 7}}));
    assert(knightBWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((knightBWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 7}}));

    const Actions& bishopCWActions = actionsPlaces.getActions(Point{2, 7});
    assert(bishopCWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(bishopCWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((bishopCWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{1, 6}, Point{3, 6}}));
    assert((bishopCWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 7}}));
    assert(bishopCWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((bishopCWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{0, 7}}));

    const Actions& queenWActions = actionsPlaces.getActions(Point{3, 7});
    assert(queenWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(queenWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((queenWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{2, 7}, Point{4, 7}, Point{2, 6}, Point{3, 6}, Point{4, 6}}));
    assert((queenWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{4, 7}}));
    assert((queenWActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{1, 7}, Point{5, 7}, Point{3, 1}}));
    assert(queenWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& kingWActions = actionsPlaces.getActions(Point{4, 7});
    assert(kingWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(kingWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((kingWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{3, 7}, Point{5, 7}, Point{3, 6}, Point{4, 6}, Point{5, 6}}));
    assert((kingWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{3, 7}}));
    assert(kingWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(kingWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& bishopFWActions = actionsPlaces.getActions(Point{5, 7});
    assert(bishopFWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(bishopFWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((bishopFWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{4, 6}, Point{6, 6}}));
    assert((bishopFWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{4, 7}}));
    assert(bishopFWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((bishopFWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 7}, Point{7, 7}}));

    const Actions& knightGWActions = actionsPlaces.getActions(Point{6, 7});
    assert((knightGWActions.get(Action::Type::PLACE).get(Action::Relation::TO) == PointSet{Point{5, 5}, Point{7, 5}}));
    assert(knightGWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((knightGWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{4, 6}}));
    assert((knightGWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY) == PointSet{Point{7, 7}}));
    assert(knightGWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(knightGWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& rookHWActions = actionsPlaces.getActions(Point{7, 7});
    assert(rookHWActions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert(rookHWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert((rookHWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO) == PointSet{Point{6, 7}, Point{7, 6}}));
    assert(rookHWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert((rookHWActions.get(Action::Type::XRAY).get(Action::Relation::TO) == PointSet{Point{5, 7}, Point{7, 1}}));
    assert(rookHWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnAWActions = actionsPlaces.getActions(Point{0, 6});
    assert_point_sets_are_equal(pawnAWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{0, 4}, {0, 5}}));
    assert(pawnAWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnAWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnAWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{0, 7}}));
    assert(pawnAWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnAWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{0, 0}}));

    const Actions& pawnBWActions = actionsPlaces.getActions(Point{1, 6});
    assert_point_sets_are_equal(pawnBWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{1, 4}, {1, 5}}));
    assert(pawnBWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnBWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnBWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{2, 7}}));
    assert(pawnBWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnBWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnCWActions = actionsPlaces.getActions(Point{2, 6});
    assert_point_sets_are_equal(pawnCWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{2, 4}, {2, 5}}));
    assert(pawnCWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnCWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnCWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{3, 7}}));
    assert(pawnCWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnCWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnDWActions = actionsPlaces.getActions(Point{3, 6});
    assert_point_sets_are_equal(pawnDWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{3, 4}, {3, 5}}));
    assert(pawnDWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnDWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnDWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{1, 7}, Point{2, 7}, Point{3, 7}, Point{4, 7}}));
    assert(pawnDWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnDWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{3, 0}}));

    const Actions& pawnEWActions = actionsPlaces.getActions(Point{4, 6});
    assert_point_sets_are_equal(pawnEWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{4, 4}, {4, 5}}));
    assert(pawnEWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnEWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnEWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{3, 7}, Point{4, 7}, Point{5, 7}, Point{6, 7}}));
    assert(pawnEWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnEWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnFWActions = actionsPlaces.getActions(Point{5, 6});
    assert_point_sets_are_equal(pawnFWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{5, 4}, {5, 5}}));
    assert(pawnFWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnFWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnFWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{4, 7}}));
    assert(pawnFWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnFWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnGWActions = actionsPlaces.getActions(Point{6, 6});
    assert_point_sets_are_equal(pawnGWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{6, 4}, {6, 5}}));
    assert(pawnGWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnGWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnGWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{5, 7}}));
    assert(pawnGWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(pawnGWActions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& pawnHWActions = actionsPlaces.getActions(Point{7, 6});
    assert_point_sets_are_equal(pawnHWActions.get(Action::Type::PLACE).get(Action::Relation::TO), (PointSet{{7, 4}, {7, 5}}));
    assert(pawnHWActions.get(Action::Type::PLACE).get(Action::Relation::BY).empty());
    assert(pawnHWActions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert((pawnHWActions.get(Action::Type::SUPPORT).get(Action::Relation::BY)== PointSet{Point{7, 7}}));
    assert(pawnHWActions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert((pawnHWActions.get(Action::Type::XRAY).get(Action::Relation::BY) == PointSet{Point{7, 0}}));

    const Actions& squareA3Actions = actionsPlaces.getActions(Point{0, 5});
    assert(squareA3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareA3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{0, 6}, Point{1, 7}}));
    assert(squareA3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareA3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareA3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareA3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareB3Actions = actionsPlaces.getActions(Point{1, 5});
    assert(squareB3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareB3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{1, 6}}));
    assert(squareB3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareB3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareB3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareB3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareC3Actions = actionsPlaces.getActions(Point{2, 5});
    assert(squareC3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareC3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{2, 6}, Point{1, 7}}));
    assert(squareC3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareC3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareC3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareC3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareD3Actions = actionsPlaces.getActions(Point{3, 5});
    assert(squareD3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareD3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{3, 6}}));
    assert(squareD3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareD3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareD3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareD3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareE3Actions = actionsPlaces.getActions(Point{4, 5});
    assert(squareE3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareE3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{4, 6}}));
    assert(squareE3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareE3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareE3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareE3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareF3Actions = actionsPlaces.getActions(Point{5, 5});
    assert(squareF3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareF3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{5, 6}, Point{6, 7}}));
    assert(squareF3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareF3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareF3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareF3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareG3Actions = actionsPlaces.getActions(Point{6, 5});
    assert(squareG3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareG3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{6, 6}}));
    assert(squareG3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareG3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareG3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareG3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());

    const Actions& squareH3Actions = actionsPlaces.getActions(Point{7, 5});
    assert(squareH3Actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty());
    assert((squareH3Actions.get(Action::Type::PLACE).get(Action::Relation::BY) == PointSet{Point{7, 6}, Point{6, 7}}));
    assert(squareH3Actions.get(Action::Type::SUPPORT).get(Action::Relation::TO).empty());
    assert(squareH3Actions.get(Action::Type::SUPPORT).get(Action::Relation::BY).empty());
    assert(squareH3Actions.get(Action::Type::XRAY).get(Action::Relation::TO).empty());
    assert(squareH3Actions.get(Action::Type::XRAY).get(Action::Relation::BY).empty());
};
