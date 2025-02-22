#include "handler.h"
#include <cassert>
#include <iostream>
#include <vector>

void test_direction() {
    Direction d{1, 2, 5};
    assert(d.dx == 1);
    assert(d.dy == 2);
    assert(d.maxDistance == 5);
    assert((d == Direction{1, 2, 5}));
}

void test_point() {
    Point p{3, 6};
    assert(p.x() == 3 && p.y() == 6 && p.hash() == 63);
    assert((p == Point{3, 6}));
    assert(p.isValid());
    assert(p.toString() == "(3, 6)");

    p = p.next(Direction{-1, 2});
    assert(p.x() == 2 && p.y() == 8 && p.hash() == 82);
    assert((p == Point{2, 8}));
    assert(!p.isValid());
    assert(p.toString() == "(2, 8)");
}

void test_piece() {
    Piece king{PieceType::KING, false};
    assert(static_cast<int>(king.type) == 0);
    assert(king.getColorName() == "black");
    assert(king.getPlaceDirections() == king.getThreatDirections());
    assert((king.getPlaceDirections()[0] == Direction{-1, -1}));
    assert((king.getPlaceDirections()[1] == Direction{0, -1}));
    assert((king.getPlaceDirections()[2] == Direction{1, -1}));
    assert((king.getPlaceDirections()[3] == Direction{-1, 0}));
    assert((king.getPlaceDirections()[4] == Direction{1, 0}));
    assert((king.getPlaceDirections()[5] == Direction{-1, 1}));
    assert((king.getPlaceDirections()[6] == Direction{0, 1}));
    assert((king.getPlaceDirections()[7] == Direction{1, 1}));

    Piece queen{PieceType::QUEEN, true};
    assert(static_cast<int>(queen.type) == 1);
    assert(queen.getColorName() == "white");
    assert(queen.getPlaceDirections() == queen.getThreatDirections());
    assert((queen.getPlaceDirections()[0] == Direction{-1, -1, 7}));
    assert((queen.getPlaceDirections()[1] == Direction{0, -1, 7}));
    assert((queen.getPlaceDirections()[2] == Direction{1, -1, 7}));
    assert((queen.getPlaceDirections()[3] == Direction{-1, 0, 7}));
    assert((queen.getPlaceDirections()[4] == Direction{1, 0, 7}));
    assert((queen.getPlaceDirections()[5] == Direction{-1, 1, 7}));
    assert((queen.getPlaceDirections()[6] == Direction{0, 1, 7}));
    assert((queen.getPlaceDirections()[7] == Direction{1, 1, 7}));

    Piece rook{PieceType::ROOK, false};
    assert(static_cast<int>(rook.type) == 2);
    assert(rook.getColorName() == "black");
    assert(rook.getPlaceDirections() == rook.getThreatDirections());
    assert((rook.getPlaceDirections()[0] == Direction{0, -1, 7}));
    assert((rook.getPlaceDirections()[1] == Direction{-1, 0, 7}));
    assert((rook.getPlaceDirections()[2] == Direction{1, 0, 7}));
    assert((rook.getPlaceDirections()[3] == Direction{0, 1, 7}));

    Piece bishop{PieceType::BISHOP, true};
    assert(static_cast<int>(bishop.type) == 3);
    assert(bishop.getColorName() == "white");
    assert(bishop.getPlaceDirections() == bishop.getThreatDirections());
    assert((bishop.getPlaceDirections()[0] == Direction{-1, -1, 7}));
    assert((bishop.getPlaceDirections()[1] == Direction{1, -1, 7}));
    assert((bishop.getPlaceDirections()[2] == Direction{-1, 1, 7}));
    assert((bishop.getPlaceDirections()[3] == Direction{1, 1, 7}));

    Piece knight{PieceType::KNIGHT, false};
    assert(static_cast<int>(knight.type) == 4);
    assert(knight.getColorName() == "black");
    assert(knight.getPlaceDirections() == knight.getThreatDirections());
    assert((knight.getPlaceDirections()[0] == Direction{-1, -2}));
    assert((knight.getPlaceDirections()[1] == Direction{1, -2}));
    assert((knight.getPlaceDirections()[2] == Direction{-2, -1}));
    assert((knight.getPlaceDirections()[3] == Direction{2, -1}));
    assert((knight.getPlaceDirections()[4] == Direction{-2, 1}));
    assert((knight.getPlaceDirections()[5] == Direction{2, 1}));
    assert((knight.getPlaceDirections()[6] == Direction{-1, 2}));
    assert((knight.getPlaceDirections()[7] == Direction{1, 2}));

    Piece pawn1{PieceType::PAWN, true};
    assert(static_cast<int>(pawn1.type) == 5);
    assert(pawn1.getColorName() == "white");
    assert(pawn1.getPlaceDirections() != pawn1.getThreatDirections());
    assert((pawn1.getPlaceDirections()[0] == Direction{0, 1}));
    assert((pawn1.getThreatDirections()[0] == Direction{-1, 1}));
    assert((pawn1.getThreatDirections()[1] == Direction{1, 1}));

    Piece pawn2{PieceType::PAWN, false};
    assert(static_cast<int>(pawn2.type) == 5);
    assert(pawn2.getColorName() == "black");
    assert(pawn2.getPlaceDirections() != pawn2.getThreatDirections());
    assert((pawn2.getPlaceDirections()[0] == Direction{0, -1}));
    assert((pawn2.getThreatDirections()[0] == Direction{-1, -1}));
    assert((pawn2.getThreatDirections()[1] == Direction{1, -1}));

    assert(pawn1.hasSameColor(&queen));
    assert(!pawn1.hasSameColor(&pawn2));
}

void test_piece_pack() {
    for (bool isWhiteColor : {true, false}) {
        PiecePack piece_pack{isWhiteColor};

        assert(piece_pack.king.type == PieceType::KING);
        assert(piece_pack.king.isWhiteColor == isWhiteColor);

        assert(piece_pack.queens.size() == 1);
        assert(piece_pack.queens[0].type == PieceType::QUEEN);
        assert(piece_pack.queens[0].isWhiteColor == isWhiteColor);

        assert(piece_pack.rooks.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piece_pack.rooks[i].type == PieceType::ROOK);
            assert(piece_pack.rooks[i].isWhiteColor == isWhiteColor);
        }

        assert(piece_pack.bishops.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piece_pack.bishops[i].type == PieceType::BISHOP);
            assert(piece_pack.bishops[i].isWhiteColor == isWhiteColor);
        }

        assert(piece_pack.knights.size() == 2);
        for (int i = 0; i < 2; ++i) {
            assert(piece_pack.knights[i].type == PieceType::KNIGHT);
            assert(piece_pack.knights[i].isWhiteColor == isWhiteColor);
        }

        assert(piece_pack.pawns.size() == 8);
        for (int i = 0; i < 8; ++i) {
            assert(piece_pack.pawns[i].type == PieceType::PAWN);
            assert(piece_pack.pawns[i].isWhiteColor == isWhiteColor);
        }
    }
}

void test_action() {
    Action action{};
    Square square1{"e3"};
    Square square2{"g7"};

    action.insert(ActionRelation::TO, square1.point);

    ActionHashes toValues = action.get(ActionRelation::TO);
    assert(toValues.size() == 1);
    assert(toValues.find(square1.point.hash()) != toValues.end());

    action.insert(ActionRelation::BY, square2.point);

    ActionHashes byValues = action.get(ActionRelation::BY);
    assert(byValues.size() == 1);
    assert(byValues.find(square2.point.hash()) != byValues.end());

    action.clear();

    assert(action.get(ActionRelation::TO).empty());
    assert(action.get(ActionRelation::BY).empty());
}

void test_actions() {
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
}

void test_square() {
    Square s1{Point{7, 3}};
    assert((s1.point == Point{7, 3}));
    assert(s1.isLightColor);
    assert(s1.getName() == "h5");
    assert(s1.getColorName() == "light");
    assert(s1.toString() == "h5 (7, 3) light");

    Square s2{1, 4};
    assert((s2.point == Point{1, 4}));
    assert(!s2.isLightColor);
    assert(s2.getName() == "b4");
    assert(s2.getColorName() == "dark");
    assert(s2.toString() == "b4 (1, 4) dark");

    Square s3{"d1"};
    assert((s3.point == Point{3, 7}));
    assert(s3.isLightColor);
    assert(s3.getName() == "d1");
    assert(s3.getColorName() == "light");
    assert(s3.toString() == "d1 (3, 7) light");

    Square emptySquare{"a1"};
    assert((emptySquare.point == Point{0, 7}));
    assert(!Square::hasPiece(emptySquare));

    Piece king{PieceType::KING, true};
    Square square{"b8", &king};
    assert((square.point == Point{1, 0}));
    assert(square.getPiece()->isKing());
    assert(square.getPiece()->isWhiteColor);
    assert(Square::hasPiece(square));
}

void test_board() {
    Board board{};

    int i = 0;
    for (Square* square : board.squares()) {
        assert(square->getPiece() == nullptr);
        assert((square->point == Point{i % 8, i / 8}));
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (Square* square : board.squaresWithPieces()) {
        ++i;
    }
    assert(i == 0);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        assert((square->point == Point{1 + i, 2 + i}));
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        assert((square->point == Point{1 + i, 2 + i}));
    }
    assert(i == 5);

    Point piecePoint{5, 3};
    Piece king{PieceType::KING, true};
    board.placePiece(&king, piecePoint);

    i = 0;
    for (Square* square : board.squaresWithPieces()) {
        assert(square->getPiece() != nullptr);
        assert(square->getPiece()->isKing());
        assert(square->getPiece()->isWhiteColor);
        assert(square->point == piecePoint);
        ++i;
    }
    assert(i == 1);

    Square squareWithPiece = board.getSquare(piecePoint);
    assert(squareWithPiece.getPiece() != nullptr);
    assert(squareWithPiece.getPiece()->isKing());
    assert(squareWithPiece.getPiece()->isWhiteColor);

    Square squareWithoutPiece = board.getSquare(Point{1, 2});
    assert(squareWithoutPiece.getPiece() == nullptr);
}

void test_initial_pieces() {
    Handler handler{};

    int i = 0;
    for (Square* square : handler.getBoard().squares()) {
        if (square->point.y() > 1 && square->point.y() < 6) {
            assert(square->getPiece() == nullptr);
        } else {
            assert(square->getPiece() != nullptr);
        }

        if (square->point.y() == 0 || square->point.y() == 7) {
            assert(!square->getPiece()->isWhiteColor == (square->point.y() == 7));
            if (square->point.x() == 0 || square->point.x() == 7) {
                assert(square->getPiece()->type == PieceType::ROOK);
            } else if (square->point.x() == 1 || square->point.x() == 6) {
                assert(square->getPiece()->type == PieceType::KNIGHT);
            } else if (square->point.x() == 2 || square->point.x() == 5) {
                assert(square->getPiece()->type == PieceType::BISHOP);
            } else if (square->point.x() == 3) {
                assert(square->getPiece()->type == PieceType::QUEEN);
            } else {
                assert(square->getPiece()->type == PieceType::KING);
            }
        } else if (square->point.y() == 1 || square->point.y() == 6) {
            assert(!square->getPiece()->isWhiteColor == (square->point.y() == 6));
            assert(square->getPiece()->type == PieceType::PAWN);
        }
        ++i;
    }
    assert(i == 64);
}

void test_initial_actions() {
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
        assert((rookA.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 1, yRows[i][1] * 10}));
        assert(rookA.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookA.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 2, yRows[i][6] * 10}));
        assert(rookA.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square knightB = board.getSquare(Point{1, yRows[i][0]});
        assert((knightB.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10, yRows[i][2] * 10 + 2}));
        assert(knightB.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 3}));
        assert((knightB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10}));
        assert(knightB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((knightB.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));

        Square bishopC = board.getSquare(Point{2, yRows[i][0]});
        assert(bishopC.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopC.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopC.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 1, yRows[i][1] * 10 + 3}));
        assert((bishopC.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));
        assert(bishopC.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopC.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10}));

        Square queen = board.getSquare(Point{3, yRows[i][0]});
        assert(queen.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(queen.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((queen.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 2, yRows[i][0] * 10 + 4, yRows[i][1] * 10 + 2, yRows[i][1] * 10 + 3, yRows[i][1] * 10 + 4}));
        assert((queen.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 4}));
        assert((queen.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 1, yRows[i][0] * 10 + 5, yRows[i][6] * 10 + 3}));
        assert(queen.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square king = board.getSquare(Point{4, yRows[i][0]});
        assert(king.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(king.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((king.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 5, yRows[i][1] * 10 + 3, yRows[i][1] * 10 + 4, yRows[i][1] * 10 + 5}));
        assert((king.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));
        assert(king.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(king.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square bishopF = board.getSquare(Point{5, yRows[i][0]});
        assert(bishopF.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopF.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopF.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 4, yRows[i][1] * 10 + 6}));
        assert((bishopF.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 4}));
        assert(bishopF.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopF.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 7}));

        Square knightG = board.getSquare(Point{6, yRows[i][0]});
        assert((knightG.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 5, yRows[i][2] * 10 + 7}));
        assert(knightG.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightG.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 4}));
        assert((knightG.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 7}));
        assert(knightG.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(knightG.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square rookH = board.getSquare(Point{7, yRows[i][0]});
        assert(rookH.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(rookH.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((rookH.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 6, yRows[i][1] * 10 + 7}));
        assert(rookH.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookH.getActions().get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 5, yRows[i][6] * 10 + 7}));
        assert(rookH.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnA = board.getSquare(Point{0, yRows[i][1]});
        assert((pawnA.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10}));
        assert(pawnA.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnA.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnA.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10}));
        assert(pawnA.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnA.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10}));

        Square pawnB = board.getSquare(Point{1, yRows[i][1]});
        assert((pawnB.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 1}));
        assert(pawnB.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnB.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnB.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 2}));
        assert(pawnB.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnB.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnC = board.getSquare(Point{2, yRows[i][1]});
        assert((pawnC.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 2}));
        assert(pawnC.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnC.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnC.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 3}));
        assert(pawnC.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnC.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnD = board.getSquare(Point{3, yRows[i][1]});
        assert((pawnD.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 3}));
        assert(pawnD.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnD.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnD.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 1, yRows[i][0] * 10 + 2, yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 4}));
        assert(pawnD.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnD.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10 + 3}));

        Square pawnE = board.getSquare(Point{4, yRows[i][1]});
        assert((pawnE.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 4}));
        assert(pawnE.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnE.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnE.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 4, yRows[i][0] * 10 + 5, yRows[i][0] * 10 + 6}));
        assert(pawnE.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnE.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnF = board.getSquare(Point{5, yRows[i][1]});
        assert((pawnF.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 5}));
        assert(pawnF.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnF.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnF.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 4}));
        assert(pawnF.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnF.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnG = board.getSquare(Point{6, yRows[i][1]});
        assert((pawnG.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 6}));
        assert(pawnG.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnG.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnG.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 5}));
        assert(pawnG.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnG.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square pawnH = board.getSquare(Point{7, yRows[i][1]});
        assert((pawnH.getActions().get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 7}));
        assert(pawnH.getActions().get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnH.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnH.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 7}));
        assert(pawnH.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnH.getActions().get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10 + 7}));

        Square squareA2 = board.getSquare(Point{0, yRows[i][2]});
        assert(squareA2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareA2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10, yRows[i][0] * 10 + 1}));
        assert(squareA2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareA2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareA2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareA2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareB2 = board.getSquare(Point{1, yRows[i][2]});
        assert(squareB2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareB2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 1}));
        assert(squareB2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareB2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareB2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareB2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareC2 = board.getSquare(Point{2, yRows[i][2]});
        assert(squareC2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareC2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 2, yRows[i][0] * 10 + 1}));
        assert(squareC2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareC2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareC2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareC2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareD2 = board.getSquare(Point{3, yRows[i][2]});
        assert(squareD2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareD2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 3}));
        assert(squareD2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareD2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareD2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareD2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareE2 = board.getSquare(Point{4, yRows[i][2]});
        assert(squareE2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareE2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 4}));
        assert(squareE2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareE2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareE2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareE2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareF2 = board.getSquare(Point{5, yRows[i][2]});
        assert(squareF2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareF2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 5, yRows[i][0] * 10 + 6}));
        assert(squareF2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareF2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareF2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareF2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareG2 = board.getSquare(Point{6, yRows[i][2]});
        assert(squareG2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareG2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 6}));
        assert(squareG2.getActions().get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(squareG2.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(squareG2.getActions().get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(squareG2.getActions().get(ActionType::XRAY).get(ActionRelation::BY).empty());

        Square squareH2 = board.getSquare(Point{7, yRows[i][2]});
        assert(squareH2.getActions().get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((squareH2.getActions().get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 7, yRows[i][0] * 10 + 6}));
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
}

int main() {
    test_direction();
    test_point();
    test_piece();
    test_piece_pack();
    test_action();
    test_actions();
    test_square();
    test_board();
    test_initial_pieces();
    test_initial_actions();

    std::cout << "OK" << std::endl;
}
