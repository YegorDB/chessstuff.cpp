#include "test_handler.h"

void testInitialActions() {
    Handler handler{};
    const ActionsPlaces& actionsPlaces = handler.getActionsPlaces();

    for (auto [point, actions] : actionsPlaces.getItems()) {
        assert(actions.get(ActionType::BIND).get(ActionRelation::TO).empty());
        assert(actions.get(ActionType::BIND).get(ActionRelation::BY).empty());
    }

    for (int y : {0, 1, 2}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        }
    }

    for (int y : {3, 4}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
            assert(actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
            assert(actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
            assert(actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
            assert(actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
        }
    }

    for (int y : {5, 6, 7}) {
        for (int x = 0; x < 8; ++x) {
            const Actions& actions = actionsPlaces.getActions(Point{x, y});
            assert(actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
            assert(actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());
        }
    }

    const Actions& rookABActions = actionsPlaces.getActions(Point{0, 0});
    assert((rookABActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 0}, Point{0, 1}}));
    assert(rookABActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookABActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{2, 0}, Point{0, 6}}));
    assert(rookABActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(rookABActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(rookABActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& knightBBActions = actionsPlaces.getActions(Point{1, 0});
    assert((knightBBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 1}}));
    assert((knightBBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(knightBBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((knightBBActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert((knightBBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(knightBBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& bishopCBActions = actionsPlaces.getActions(Point{2, 0});
    assert((bishopCBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 1}, Point{3, 1}}));
    assert((bishopCBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(bishopCBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopCBActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(bishopCBActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(bishopCBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& queenBActions = actionsPlaces.getActions(Point{3, 0});
    assert((queenBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{2, 0}, Point{4, 0}, Point{2, 1}, Point{3, 1}, Point{4, 1}}));
    assert((queenBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert((queenBActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{1, 0}, Point{5, 0}, Point{3, 6}}));
    assert(queenBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(queenBActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(queenBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& kingBActions = actionsPlaces.getActions(Point{4, 0});
    assert((kingBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 0}, Point{5, 0}, Point{3, 1}, Point{4, 1}, Point{5, 1}}));
    assert((kingBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(kingBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(kingBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(kingBActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(kingBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& bishopFBActions = actionsPlaces.getActions(Point{5, 0});
    assert((bishopFBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 1}, Point{6, 1}}));
    assert((bishopFBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert(bishopFBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopFBActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}, Point{7, 0}}));
    assert(bishopFBActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(bishopFBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& knightGBActions = actionsPlaces.getActions(Point{6, 0});
    assert((knightGBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 1}}));
    assert((knightGBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 0}}));
    assert(knightGBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(knightGBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((knightGBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(knightGBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& rookHBActions = actionsPlaces.getActions(Point{7, 0});
    assert((rookHBActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{6, 0}, Point{7, 1}}));
    assert(rookHBActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookHBActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{5, 0}, Point{7, 6}}));
    assert(rookHBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(rookHBActions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(rookHBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnABActions = actionsPlaces.getActions(Point{0, 1});
    assert(pawnABActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnABActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(pawnABActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnABActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 7}}));
    assert((pawnABActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{1, 2}}));
    assert(pawnABActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnBBActions = actionsPlaces.getActions(Point{1, 1});
    assert(pawnBBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnBBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{2, 0}}));
    assert(pawnBBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnBBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnBBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(pawnBBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnCBActions = actionsPlaces.getActions(Point{2, 1});
    assert(pawnCBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnCBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(pawnCBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnCBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnCBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{1, 2}, Point{3, 2}}));
    assert(pawnCBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnDBActions = actionsPlaces.getActions(Point{3, 1});
    assert(pawnDBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnDBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{2, 0}, Point{3, 0}, Point{4, 0}}));
    assert(pawnDBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnDBActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert((pawnDBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{2, 2}, Point{4, 2}}));
    assert(pawnDBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnEBActions = actionsPlaces.getActions(Point{4, 1});
    assert(pawnEBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnEBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}, Point{4, 0}, Point{5, 0}, Point{6, 0}}));
    assert(pawnEBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnEBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnEBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{3, 2}, Point{5, 2}}));
    assert(pawnEBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnFBActions = actionsPlaces.getActions(Point{5, 1});
    assert(pawnFBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnFBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert(pawnFBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnFBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnFBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{4, 2}, Point{6, 2}}));
    assert(pawnFBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnGBActions = actionsPlaces.getActions(Point{6, 1});
    assert(pawnGBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnGBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{5, 0}}));
    assert(pawnGBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnGBActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnGBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(pawnGBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& pawnHBActions = actionsPlaces.getActions(Point{7, 1});
    assert(pawnHBActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnHBActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 0}}));
    assert(pawnHBActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnHBActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{7, 7}}));
    assert((pawnHBActions.get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{6, 2}}));
    assert(pawnHBActions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    const Actions& squareA6Actions = actionsPlaces.getActions(Point{0, 2});
    assert(squareA6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareA6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareA6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareA6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareA6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareA6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{1, 1}}));

    const Actions& squareB6Actions = actionsPlaces.getActions(Point{1, 2});
    assert(squareB6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareB6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareB6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareB6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareB6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareB6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{0, 1}, Point{2, 1}}));

    const Actions& squareC6Actions = actionsPlaces.getActions(Point{2, 2});
    assert(squareC6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareC6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareC6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareC6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareC6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareC6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{1, 1}, Point{3, 1}}));

    const Actions& squareD6Actions = actionsPlaces.getActions(Point{3, 2});
    assert(squareD6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareD6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareD6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareD6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareD6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareD6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{2, 1}, Point{4, 1}}));

    const Actions& squareE6Actions = actionsPlaces.getActions(Point{4, 2});
    assert(squareE6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareE6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareE6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareE6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareE6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareE6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{3, 1}, Point{5, 1}}));

    const Actions& squareF6Actions = actionsPlaces.getActions(Point{5, 2});
    assert(squareF6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareF6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareF6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareF6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareF6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareF6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{6, 0}, Point{4, 1}, Point{6, 1}}));

    const Actions& squareG6Actions = actionsPlaces.getActions(Point{6, 2});
    assert(squareG6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareG6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareG6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareG6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareG6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareG6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{5, 1}, Point{7, 1}}));

    const Actions& squareH6Actions = actionsPlaces.getActions(Point{7, 2});
    assert(squareH6Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareH6Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareH6Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareH6Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareH6Actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareH6Actions.get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{6, 0}, Point{6, 1}}));

    const Actions& rookAWActions = actionsPlaces.getActions(Point{0, 7});
    assert(rookAWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(rookAWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((rookAWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 7}, Point{0, 6}}));
    assert(rookAWActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookAWActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{2, 7}, Point{0, 1}}));
    assert(rookAWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& knightBWActions = actionsPlaces.getActions(Point{1, 7});
    assert((knightBWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, 5}, Point{2, 5}}));
    assert(knightBWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((knightBWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 6}}));
    assert((knightBWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 7}}));
    assert(knightBWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((knightBWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}}));

    const Actions& bishopCWActions = actionsPlaces.getActions(Point{2, 7});
    assert(bishopCWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopCWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((bishopCWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 6}, Point{3, 6}}));
    assert((bishopCWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert(bishopCWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopCWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 7}}));

    const Actions& queenWActions = actionsPlaces.getActions(Point{3, 7});
    assert(queenWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(queenWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((queenWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{2, 7}, Point{4, 7}, Point{2, 6}, Point{3, 6}, Point{4, 6}}));
    assert((queenWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 7}}));
    assert((queenWActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{1, 7}, Point{5, 7}, Point{3, 1}}));
    assert(queenWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& kingWActions = actionsPlaces.getActions(Point{4, 7});
    assert(kingWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(kingWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((kingWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 7}, Point{5, 7}, Point{3, 6}, Point{4, 6}, Point{5, 6}}));
    assert((kingWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert(kingWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(kingWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& bishopFWActions = actionsPlaces.getActions(Point{5, 7});
    assert(bishopFWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopFWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((bishopFWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 6}, Point{6, 6}}));
    assert((bishopFWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 7}}));
    assert(bishopFWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopFWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}, Point{7, 7}}));

    const Actions& knightGWActions = actionsPlaces.getActions(Point{6, 7});
    assert((knightGWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, 5}, Point{7, 5}}));
    assert(knightGWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((knightGWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 6}}));
    assert((knightGWActions.get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 7}}));
    assert(knightGWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(knightGWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& rookHWActions = actionsPlaces.getActions(Point{7, 7});
    assert(rookHWActions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(rookHWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((rookHWActions.get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{6, 7}, Point{7, 6}}));
    assert(rookHWActions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookHWActions.get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{5, 7}, Point{7, 1}}));
    assert(rookHWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnAWActions = actionsPlaces.getActions(Point{0, 6});
    assert((pawnAWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, 5}}));
    assert(pawnAWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnAWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnAWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{0, 7}}));
    assert(pawnAWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnAWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 0}}));

    const Actions& pawnBWActions = actionsPlaces.getActions(Point{1, 6});
    assert((pawnBWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{1, 5}}));
    assert(pawnBWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnBWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnBWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{2, 7}}));
    assert(pawnBWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnBWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnCWActions = actionsPlaces.getActions(Point{2, 6});
    assert((pawnCWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, 5}}));
    assert(pawnCWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnCWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnCWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, 7}}));
    assert(pawnCWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnCWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnDWActions = actionsPlaces.getActions(Point{3, 6});
    assert((pawnDWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{3, 5}}));
    assert(pawnDWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnDWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnDWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{1, 7}, Point{2, 7}, Point{3, 7}, Point{4, 7}}));
    assert(pawnDWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnDWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}}));

    const Actions& pawnEWActions = actionsPlaces.getActions(Point{4, 6});
    assert((pawnEWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{4, 5}}));
    assert(pawnEWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnEWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnEWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, 7}, Point{4, 7}, Point{5, 7}, Point{6, 7}}));
    assert(pawnEWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnEWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnFWActions = actionsPlaces.getActions(Point{5, 6});
    assert((pawnFWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, 5}}));
    assert(pawnFWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnFWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnFWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{4, 7}}));
    assert(pawnFWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnFWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnGWActions = actionsPlaces.getActions(Point{6, 6});
    assert((pawnGWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{6, 5}}));
    assert(pawnGWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnGWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnGWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{5, 7}}));
    assert(pawnGWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnGWActions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& pawnHWActions = actionsPlaces.getActions(Point{7, 6});
    assert((pawnHWActions.get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{7, 5}}));
    assert(pawnHWActions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnHWActions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnHWActions.get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{7, 7}}));
    assert(pawnHWActions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnHWActions.get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{7, 0}}));

    const Actions& squareA3Actions = actionsPlaces.getActions(Point{0, 5});
    assert(squareA3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareA3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{0, 6}, Point{1, 7}}));
    assert(squareA3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareA3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareA3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareA3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareB3Actions = actionsPlaces.getActions(Point{1, 5});
    assert(squareB3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareB3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{1, 6}}));
    assert(squareB3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareB3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareB3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareB3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareC3Actions = actionsPlaces.getActions(Point{2, 5});
    assert(squareC3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareC3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{2, 6}, Point{1, 7}}));
    assert(squareC3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareC3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareC3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareC3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareD3Actions = actionsPlaces.getActions(Point{3, 5});
    assert(squareD3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareD3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{3, 6}}));
    assert(squareD3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareD3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareD3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareD3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareE3Actions = actionsPlaces.getActions(Point{4, 5});
    assert(squareE3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareE3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{4, 6}}));
    assert(squareE3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareE3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareE3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareE3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareF3Actions = actionsPlaces.getActions(Point{5, 5});
    assert(squareF3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareF3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{5, 6}, Point{6, 7}}));
    assert(squareF3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareF3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareF3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareF3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareG3Actions = actionsPlaces.getActions(Point{6, 5});
    assert(squareG3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareG3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{6, 6}}));
    assert(squareG3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareG3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareG3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareG3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

    const Actions& squareH3Actions = actionsPlaces.getActions(Point{7, 5});
    assert(squareH3Actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareH3Actions.get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{7, 6}, Point{6, 7}}));
    assert(squareH3Actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareH3Actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareH3Actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareH3Actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
};
