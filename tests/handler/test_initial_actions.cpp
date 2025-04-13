#include "test_handler.h"

void testInitialActions() {
    Handler handler{};
    Board board = handler.getBoard();

    for (Square* square : board.squares()) {
        assert(square->getActions().get(ActionType::THREAT).get(ActionRelation::TO).empty());
        assert(square->getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty());
        assert(square->getActions().get(ActionType::BIND).get(ActionRelation::TO).empty());
        assert(square->getActions().get(ActionType::BIND).get(ActionRelation::BY).empty());
    }

    for (int i : {0, 1}) {
        std::vector<std::vector<int>> yRows{
            {0, 1, 2, 3, 4, 5, 6, 7},
            {7, 6, 5, 4, 3, 2, 1, 0}
        };

        Square rookA = board.getSquare(Point{0, yRows[i][0]});
        assert(rookA.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(rookA.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((rookA.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, yRows[i][0]}, Point{0, yRows[i][1]}}));
        assert(rookA.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookA.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{2, yRows[i][0]}, Point{0, yRows[i][6]}}));
        assert(rookA.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square knightB = board.getSquare(Point{1, yRows[i][0]});
        assert((knightB.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, yRows[i][2]}, Point{2, yRows[i][2]}}));
        assert(knightB.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, yRows[i][1]}}));
        assert((knightB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{0, yRows[i][0]}}));
        assert(knightB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((knightB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][0]}}));

        Square bishopC = board.getSquare(Point{2, yRows[i][0]});
        assert(bishopC.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopC.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopC.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{1, yRows[i][1]}, Point{3, yRows[i][1]}}));
        assert((bishopC.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][0]}}));
        assert(bishopC.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopC.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, yRows[i][0]}}));

        Square queen = board.getSquare(Point{3, yRows[i][0]});
        assert(queen.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(queen.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((queen.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{2, yRows[i][0]}, Point{4, yRows[i][0]}, Point{2, yRows[i][1]}, Point{3, yRows[i][1]}, Point{4, yRows[i][1]}}));
        assert((queen.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, yRows[i][0]}}));
        assert((queen.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{1, yRows[i][0]}, Point{5, yRows[i][0]}, Point{3, yRows[i][6]}}));
        assert(queen.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square king = board.getSquare(Point{4, yRows[i][0]});
        assert(king.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(king.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((king.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{3, yRows[i][0]}, Point{5, yRows[i][0]}, Point{3, yRows[i][1]}, Point{4, yRows[i][1]}, Point{5, yRows[i][1]}}));
        assert((king.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][0]}}));
        assert(king.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(king.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square bishopF = board.getSquare(Point{5, yRows[i][0]});
        assert(bishopF.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopF.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopF.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, yRows[i][1]}, Point{6, yRows[i][1]}}));
        assert((bishopF.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{4, yRows[i][0]}}));
        assert(bishopF.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopF.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][0]}, Point{7, yRows[i][0]}}));

        Square knightG = board.getSquare(Point{6, yRows[i][0]});
        assert((knightG.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, yRows[i][2]}, Point{7, yRows[i][2]}}));
        assert(knightG.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightG.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{4, yRows[i][1]}}));
        assert((knightG.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == PointSet{Point{7, yRows[i][0]}}));
        assert(knightG.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(knightG.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square rookH = board.getSquare(Point{7, yRows[i][0]});
        assert(rookH.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(rookH.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((rookH.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == PointSet{Point{6, yRows[i][0]}, Point{7, yRows[i][1]}}));
        assert(rookH.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookH.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == PointSet{Point{5, yRows[i][0]}, Point{7, yRows[i][6]}}));
        assert(rookH.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnA = board.getSquare(Point{0, yRows[i][1]});
        assert((pawnA.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{0, yRows[i][2]}}));
        assert(pawnA.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnA.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnA.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{0, yRows[i][0]}}));
        assert(pawnA.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnA.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{0, yRows[i][7]}}));

        Square pawnB = board.getSquare(Point{1, yRows[i][1]});
        assert((pawnB.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{1, yRows[i][2]}}));
        assert(pawnB.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{2, yRows[i][0]}}));
        assert(pawnB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnC = board.getSquare(Point{2, yRows[i][1]});
        assert((pawnC.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{2, yRows[i][2]}}));
        assert(pawnC.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnC.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnC.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, yRows[i][0]}}));
        assert(pawnC.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnC.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnD = board.getSquare(Point{3, yRows[i][1]});
        assert((pawnD.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{3, yRows[i][2]}}));
        assert(pawnD.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnD.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnD.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{1, yRows[i][0]}, Point{2, yRows[i][0]}, Point{3, yRows[i][0]}, Point{4, yRows[i][0]}}));
        assert(pawnD.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnD.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][7]}}));

        Square pawnE = board.getSquare(Point{4, yRows[i][1]});
        assert((pawnE.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{4, yRows[i][2]}}));
        assert(pawnE.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnE.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnE.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{3, yRows[i][0]}, Point{4, yRows[i][0]}, Point{5, yRows[i][0]}, Point{6, yRows[i][0]}}));
        assert(pawnE.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnE.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnF = board.getSquare(Point{5, yRows[i][1]});
        assert((pawnF.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{5, yRows[i][2]}}));
        assert(pawnF.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnF.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnF.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{4, yRows[i][0]}}));
        assert(pawnF.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnF.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnG = board.getSquare(Point{6, yRows[i][1]});
        assert((pawnG.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{6, yRows[i][2]}}));
        assert(pawnG.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnG.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnG.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{5, yRows[i][0]}}));
        assert(pawnG.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnG.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnH = board.getSquare(Point{7, yRows[i][1]});
        assert((pawnH.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == PointSet{Point{7, yRows[i][2]}}));
        assert(pawnH.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnH.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnH.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== PointSet{Point{7, yRows[i][0]}}));
        assert(pawnH.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnH.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == PointSet{Point{7, yRows[i][7]}}));

        Square squareA2 = board.getSquare(Point{0, yRows[i][2]});
        assert(squareA2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareA2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{0, yRows[i][1]}, Point{1, yRows[i][0]}}));
        assert(squareA2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareA2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareA2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareA2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareB2 = board.getSquare(Point{1, yRows[i][2]});
        assert(squareB2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareB2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{1, yRows[i][1]}}));
        assert(squareB2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareB2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareB2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareB2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareC2 = board.getSquare(Point{2, yRows[i][2]});
        assert(squareC2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareC2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{2, yRows[i][1]}, Point{1, yRows[i][0]}}));
        assert(squareC2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareC2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareC2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareC2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareD2 = board.getSquare(Point{3, yRows[i][2]});
        assert(squareD2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareD2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{3, yRows[i][1]}}));
        assert(squareD2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareD2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareD2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareD2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareE2 = board.getSquare(Point{4, yRows[i][2]});
        assert(squareE2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareE2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{4, yRows[i][1]}}));
        assert(squareE2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareE2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareE2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareE2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareF2 = board.getSquare(Point{5, yRows[i][2]});
        assert(squareF2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareF2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{5, yRows[i][1]}, Point{6, yRows[i][0]}}));
        assert(squareF2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareF2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareF2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareF2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareG2 = board.getSquare(Point{6, yRows[i][2]});
        assert(squareG2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareG2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{6, yRows[i][1]}}));
        assert(squareG2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareG2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareG2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareG2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareH2 = board.getSquare(Point{7, yRows[i][2]});
        assert(squareH2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareH2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == PointSet{Point{7, yRows[i][1]}, Point{6, yRows[i][0]}}));
        assert(squareH2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareH2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareH2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareH2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        for (int j = 0; j < 8; ++j) {
            Square square = board.getSquare(Point{j, yRows[i][3]});
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
            assert(square.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
            assert(square.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
            assert(square.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());
        }
    }
};
