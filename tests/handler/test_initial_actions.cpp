#include "test_handler.h"

void testInitialActions() {
    Handler handler{};
    Board board = handler.getBoard();

    for (Square* square : board.squares()) {
        assert(square->getActions().get(ActionType::BIND).get(ActionRelation::TO).empty());
        assert(square->getActions().get(ActionType::BIND).get(ActionRelation::BY).empty());
    }

    for (int y : {0, 1, 2}) {
        for (int x = 0; x < 8; ++x) {
            Square square = board.getSquare(Point{x, y});
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        }
    }

    for (int y : {3, 4}) {
        for (int x = 0; x < 8; ++x) {
            Square square = board.getSquare(Point{x, y});
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
            assert(square.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
            assert(square.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
        }
    }

    for (int y : {5, 6, 7}) {
        for (int x = 0; x < 8; ++x) {
            Square square = board.getSquare(Point{x, y});
            assert(square.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());
        }
    }

    Square rookAB = board.getSquare(Point{0, 0});
    assert((rookAB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 0}, Point{0, 1}}));
    assert(rookAB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookAB.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{2, 0}, Point{0, 6}}));
    assert(rookAB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(rookAB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(rookAB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square knightBB = board.getSquare(Point{1, 0});
    assert((knightBB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 1}}));
    assert((knightBB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(knightBB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((knightBB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert((knightBB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(knightBB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square bishopCB = board.getSquare(Point{2, 0});
    assert((bishopCB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 1}, Point{3, 1}}));
    assert((bishopCB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(bishopCB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopCB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(bishopCB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(bishopCB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square queenB = board.getSquare(Point{3, 0});
    assert((queenB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{2, 0}, Point{4, 0}, Point{2, 1}, Point{3, 1}, Point{4, 1}}));
    assert((queenB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert((queenB.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{1, 0}, Point{5, 0}, Point{3, 6}}));
    assert(queenB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(queenB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(queenB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square kingB = board.getSquare(Point{4, 0});
    assert((kingB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 0}, Point{5, 0}, Point{3, 1}, Point{4, 1}, Point{5, 1}}));
    assert((kingB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(kingB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(kingB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(kingB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(kingB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square bishopFB = board.getSquare(Point{5, 0});
    assert((bishopFB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 1}, Point{6, 1}}));
    assert((bishopFB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert(bishopFB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopFB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}, Point{7, 0}}));
    assert(bishopFB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(bishopFB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square knightGB = board.getSquare(Point{6, 0});
    assert((knightGB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 1}}));
    assert((knightGB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 0}}));
    assert(knightGB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(knightGB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((knightGB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(knightGB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square rookHB = board.getSquare(Point{7, 0});
    assert((rookHB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{6, 0}, Point{7, 1}}));
    assert(rookHB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookHB.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{5, 0}, Point{7, 6}}));
    assert(rookHB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(rookHB.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(rookHB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnAB = board.getSquare(Point{0, 1});
    assert(pawnAB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnAB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 0}}));
    assert(pawnAB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnAB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 7}}));
    assert((pawnAB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{1, 2}}));
    assert(pawnAB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnBB = board.getSquare(Point{1, 1});
    assert(pawnBB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnBB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{2, 0}}));
    assert(pawnBB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnBB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnBB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{0, 2}, Point{2, 2}}));
    assert(pawnBB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnCB = board.getSquare(Point{2, 1});
    assert(pawnCB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnCB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}}));
    assert(pawnCB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnCB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnCB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{1, 2}, Point{3, 2}}));
    assert(pawnCB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnDB = board.getSquare(Point{3, 1});
    assert(pawnDB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnDB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{2, 0}, Point{3, 0}, Point{4, 0}}));
    assert(pawnDB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnDB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert((pawnDB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{2, 2}, Point{4, 2}}));
    assert(pawnDB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnEB = board.getSquare(Point{4, 1});
    assert(pawnEB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnEB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 0}, Point{4, 0}, Point{5, 0}, Point{6, 0}}));
    assert(pawnEB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnEB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnEB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{3, 2}, Point{5, 2}}));
    assert(pawnEB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnFB = board.getSquare(Point{5, 1});
    assert(pawnFB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnFB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 0}}));
    assert(pawnFB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnFB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnFB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{4, 2}, Point{6, 2}}));
    assert(pawnFB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnGB = board.getSquare(Point{6, 1});
    assert(pawnGB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnGB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{5, 0}}));
    assert(pawnGB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnGB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert((pawnGB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{5, 2}, Point{7, 2}}));
    assert(pawnGB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square pawnHB = board.getSquare(Point{7, 1});
    assert(pawnHB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnHB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 0}}));
    assert(pawnHB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnHB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{7, 7}}));
    assert((pawnHB.getActions().get(ActionType::THREAT).get(ActionRelation::TO) == PointSet{Point{6, 2}}));
    assert(pawnHB.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());

    Square squareA6 = board.getSquare(Point{0, 2});
    assert(squareA6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareA6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareA6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareA6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareA6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareA6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{1, 1}}));

    Square squareB6 = board.getSquare(Point{1, 2});
    assert(squareB6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareB6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareB6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareB6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareB6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareB6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{0, 1}, Point{2, 1}}));

    Square squareC6 = board.getSquare(Point{2, 2});
    assert(squareC6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareC6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareC6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareC6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareC6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareC6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{1, 0}, Point{1, 1}, Point{3, 1}}));

    Square squareD6 = board.getSquare(Point{3, 2});
    assert(squareD6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareD6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareD6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareD6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareD6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareD6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{2, 1}, Point{4, 1}}));

    Square squareE6 = board.getSquare(Point{4, 2});
    assert(squareE6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareE6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareE6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareE6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareE6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareE6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{3, 1}, Point{5, 1}}));

    Square squareF6 = board.getSquare(Point{5, 2});
    assert(squareF6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareF6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareF6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareF6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareF6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareF6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{6, 0}, Point{4, 1}, Point{6, 1}}));

    Square squareG6 = board.getSquare(Point{6, 2});
    assert(squareG6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareG6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareG6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareG6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareG6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareG6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{5, 1}, Point{7, 1}}));

    Square squareH6 = board.getSquare(Point{7, 2});
    assert(squareH6.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareH6.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareH6.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareH6.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
    assert(squareH6.getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert((squareH6.getActions().get(ActionType::THREAT).get(ActionRelation::BY) == PointSet{Point{6, 0}, Point{6, 1}}));

    Square rookAW = board.getSquare(Point{0, 7});
    assert(rookAW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(rookAW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((rookAW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 7}, Point{0, 6}}));
    assert(rookAW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookAW.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{2, 7}, Point{0, 1}}));
    assert(rookAW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square knightBW = board.getSquare(Point{1, 7});
    assert((knightBW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, 5}, Point{2, 5}}));
    assert(knightBW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((knightBW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 6}}));
    assert((knightBW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, 7}}));
    assert(knightBW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((knightBW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}}));

    Square bishopCW = board.getSquare(Point{2, 7});
    assert(bishopCW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopCW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((bishopCW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, 6}, Point{3, 6}}));
    assert((bishopCW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert(bishopCW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopCW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 7}}));

    Square queenW = board.getSquare(Point{3, 7});
    assert(queenW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(queenW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((queenW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{2, 7}, Point{4, 7}, Point{2, 6}, Point{3, 6}, Point{4, 6}}));
    assert((queenW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 7}}));
    assert((queenW.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{1, 7}, Point{5, 7}, Point{3, 1}}));
    assert(queenW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square kingW = board.getSquare(Point{4, 7});
    assert(kingW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(kingW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((kingW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, 7}, Point{5, 7}, Point{3, 6}, Point{4, 6}, Point{5, 6}}));
    assert((kingW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, 7}}));
    assert(kingW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(kingW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square bishopFW = board.getSquare(Point{5, 7});
    assert(bishopFW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(bishopFW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((bishopFW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 6}, Point{6, 6}}));
    assert((bishopFW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, 7}}));
    assert(bishopFW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((bishopFW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 7}, Point{7, 7}}));

    Square knightGW = board.getSquare(Point{6, 7});
    assert((knightGW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, 5}, Point{7, 5}}));
    assert(knightGW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((knightGW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, 6}}));
    assert((knightGW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, 7}}));
    assert(knightGW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(knightGW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square rookHW = board.getSquare(Point{7, 7});
    assert(rookHW.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(rookHW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert((rookHW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{6, 7}, Point{7, 6}}));
    assert(rookHW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert((rookHW.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{5, 7}, Point{7, 1}}));
    assert(rookHW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnAW = board.getSquare(Point{0, 6});
    assert((pawnAW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, 5}}));
    assert(pawnAW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnAW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnAW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{0, 7}}));
    assert(pawnAW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnAW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, 0}}));

    Square pawnBW = board.getSquare(Point{1, 6});
    assert((pawnBW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{1, 5}}));
    assert(pawnBW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnBW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnBW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{2, 7}}));
    assert(pawnBW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnBW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnCW = board.getSquare(Point{2, 6});
    assert((pawnCW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, 5}}));
    assert(pawnCW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnCW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnCW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, 7}}));
    assert(pawnCW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnCW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnDW = board.getSquare(Point{3, 6});
    assert((pawnDW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{3, 5}}));
    assert(pawnDW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnDW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnDW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{1, 7}, Point{2, 7}, Point{3, 7}, Point{4, 7}}));
    assert(pawnDW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnDW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, 0}}));

    Square pawnEW = board.getSquare(Point{4, 6});
    assert((pawnEW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{4, 5}}));
    assert(pawnEW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnEW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnEW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, 7}, Point{4, 7}, Point{5, 7}, Point{6, 7}}));
    assert(pawnEW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnEW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnFW = board.getSquare(Point{5, 6});
    assert((pawnFW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, 5}}));
    assert(pawnFW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnFW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnFW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{4, 7}}));
    assert(pawnFW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnFW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnGW = board.getSquare(Point{6, 6});
    assert((pawnGW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{6, 5}}));
    assert(pawnGW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnGW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnGW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{5, 7}}));
    assert(pawnGW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(pawnGW.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square pawnHW = board.getSquare(Point{7, 6});
    assert((pawnHW.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{7, 5}}));
    assert(pawnHW.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
    assert(pawnHW.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert((pawnHW.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{7, 7}}));
    assert(pawnHW.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert((pawnHW.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{7, 0}}));

    Square squareA3 = board.getSquare(Point{0, 5});
    assert(squareA3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareA3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{0, 6}, Point{1, 7}}));
    assert(squareA3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareA3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareA3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareA3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareB3 = board.getSquare(Point{1, 5});
    assert(squareB3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareB3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{1, 6}}));
    assert(squareB3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareB3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareB3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareB3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareC3 = board.getSquare(Point{2, 5});
    assert(squareC3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareC3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{2, 6}, Point{1, 7}}));
    assert(squareC3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareC3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareC3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareC3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareD3 = board.getSquare(Point{3, 5});
    assert(squareD3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareD3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{3, 6}}));
    assert(squareD3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareD3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareD3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareD3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareE3 = board.getSquare(Point{4, 5});
    assert(squareE3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareE3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{4, 6}}));
    assert(squareE3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareE3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareE3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareE3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareF3 = board.getSquare(Point{5, 5});
    assert(squareF3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareF3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{5, 6}, Point{6, 7}}));
    assert(squareF3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareF3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareF3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareF3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareG3 = board.getSquare(Point{6, 5});
    assert(squareG3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareG3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{6, 6}}));
    assert(squareG3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareG3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareG3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareG3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

    Square squareH3 = board.getSquare(Point{7, 5});
    assert(squareH3.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert((squareH3.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{7, 6}, Point{6, 7}}));
    assert(squareH3.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(squareH3.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
    assert(squareH3.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
    assert(squareH3.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
};
