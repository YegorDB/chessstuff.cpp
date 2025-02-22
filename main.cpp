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

void test_board_item_action() {
    Action action{};
    Square square1{"e3"};
    Square square2{"g7"};

    action.insert(ActionRelation::TO, square1);

    ActionHashes toValues = action.get(ActionRelation::TO);
    assert(toValues.size() == 1);
    assert(toValues.find(square1.point.hash()) != toValues.end());

    action.insert(ActionRelation::BY, square2);

    ActionHashes byValues = action.get(ActionRelation::BY);
    assert(byValues.size() == 1);
    assert(byValues.find(square2.point.hash()) != byValues.end());

    action.clear();

    assert(action.get(ActionRelation::TO).empty());
    assert(action.get(ActionRelation::BY).empty());
}

void test_board_item_actions() {
    Actions actions{};
    Square square1{"b8"};
    Square square2{"h1"};

    actions.insert(ActionType::THREAT, ActionRelation::BY, square1);
    actions.insert(ActionType::THREAT, ActionRelation::TO, square2);
    assert(!actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());

    actions.insert(ActionType::SUPPORT, ActionRelation::TO, square1);
    actions.insert(ActionType::SUPPORT, ActionRelation::BY, square2);
    assert(!actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());

    actions.insert(ActionType::PLACE, ActionRelation::TO, square1);
    actions.insert(ActionType::PLACE, ActionRelation::BY, square2);
    assert(!actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
    assert(!actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());

    actions.insert(ActionType::XRAY, ActionRelation::TO, square1);
    actions.insert(ActionType::XRAY, ActionRelation::BY, square2);
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

void test_board_item() {
    Square emptySquare{"a1"};
    BoardItem itemWithoutPiece{emptySquare};
    assert((itemWithoutPiece.square.point == Point{0, 7}));
    assert(!BoardItem::hasPiece(itemWithoutPiece));

    Square square{"b8"};
    Piece king{PieceType::KING, true};
    BoardItem itemWithPiece{square, &king};
    assert((itemWithPiece.square.point == Point{1, 0}));
    assert((itemWithPiece.piece->type == PieceType::KING));
    assert(itemWithPiece.piece->isWhiteColor);
    assert(BoardItem::hasPiece(itemWithPiece));
}

void test_board_items() {
    BoardItems items{};

    int i = 0;
    for (BoardItem* item : items.sequence()) {
        assert(item->piece == nullptr);
        assert((item->square.point == Point{i % 8, i / 8}));
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (BoardItem* item : items.sequenceWithPieces()) {
        ++i;
    }
    assert(i == 0);

    i = 0;
    for (BoardItem* item : items.sequenceByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        assert((item->square.point == Point{1 + i, 2 + i}));
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (BoardItem* item : items.sequenceByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        assert((item->square.point == Point{1 + i, 2 + i}));
    }
    assert(i == 5);

    Point piecePoint{5, 3};
    Piece king{PieceType::KING, true};
    items.placePiece(king, piecePoint);

    i = 0;
    for (BoardItem* item : items.sequenceWithPieces()) {
        assert(item->piece != nullptr);
        assert(item->piece->type == PieceType::KING);
        assert(item->piece->isWhiteColor);
        assert(item->square.point == piecePoint);
        ++i;
    }
    assert(i == 1);

    BoardItem itemWithPiece = items.getItem(piecePoint);
    assert(itemWithPiece.piece != nullptr);
    assert(itemWithPiece.piece->type == PieceType::KING);
    assert(itemWithPiece.piece->isWhiteColor);

    BoardItem itemWithoutPiece = items.getItem(Point{1, 2});
    assert(itemWithoutPiece.piece == nullptr);
}

void test_initial_pieces() {
    Handler handler{};

    int i = 0;
    for (BoardItem* item : handler.getItems().sequence()) {
        if (item->square.point.y() > 1 && item->square.point.y() < 6) {
            assert(item->piece == nullptr);
        } else {
            assert(item->piece != nullptr);
        }

        if (item->square.point.y() == 0 || item->square.point.y() == 7) {
            assert(!item->piece->isWhiteColor == (item->square.point.y() == 7));
            if (item->square.point.x() == 0 || item->square.point.x() == 7) {
                assert(item->piece->type == PieceType::ROOK);
            } else if (item->square.point.x() == 1 || item->square.point.x() == 6) {
                assert(item->piece->type == PieceType::KNIGHT);
            } else if (item->square.point.x() == 2 || item->square.point.x() == 5) {
                assert(item->piece->type == PieceType::BISHOP);
            } else if (item->square.point.x() == 3) {
                assert(item->piece->type == PieceType::QUEEN);
            } else {
                assert(item->piece->type == PieceType::KING);
            }
        } else if (item->square.point.y() == 1 || item->square.point.y() == 6) {
            assert(!item->piece->isWhiteColor == (item->square.point.y() == 6));
            assert(item->piece->type == PieceType::PAWN);
        }
        ++i;
    }
    assert(i == 64);
}

void test_initial_actions() {
    Handler handler{};
    BoardItems items = handler.getItems();

    for (BoardItem* item : items.sequence()) {
        assert(item->actions.get(ActionType::THREAT).get(ActionRelation::TO).empty());
        assert(item->actions.get(ActionType::THREAT).get(ActionRelation::BY).empty());
        assert(item->actions.get(ActionType::BIND).get(ActionRelation::TO).empty());
        assert(item->actions.get(ActionType::BIND).get(ActionRelation::BY).empty());
    }

    for (int i : {0, 1}) {
        std::vector<std::vector<int>> yRows{
            {0, 1, 2, 3, 4, 5, 6, 7},
            {7, 6, 5, 4, 3, 2, 1, 0}
        };

        BoardItem rookA = items.getItem(Point{0, yRows[i][0]});
        assert(rookA.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(rookA.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((rookA.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 1, yRows[i][1] * 10}));
        assert(rookA.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookA.actions.get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 2, yRows[i][6] * 10}));
        assert(rookA.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem knightB = items.getItem(Point{1, yRows[i][0]});
        assert((knightB.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10, yRows[i][2] * 10 + 2}));
        assert(knightB.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightB.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 3}));
        assert((knightB.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10}));
        assert(knightB.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((knightB.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));

        BoardItem bishopC = items.getItem(Point{2, yRows[i][0]});
        assert(bishopC.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopC.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopC.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 1, yRows[i][1] * 10 + 3}));
        assert((bishopC.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));
        assert(bishopC.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopC.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10}));

        BoardItem queen = items.getItem(Point{3, yRows[i][0]});
        assert(queen.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(queen.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((queen.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 2, yRows[i][0] * 10 + 4, yRows[i][1] * 10 + 2, yRows[i][1] * 10 + 3, yRows[i][1] * 10 + 4}));
        assert((queen.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 4}));
        assert((queen.actions.get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 1, yRows[i][0] * 10 + 5, yRows[i][6] * 10 + 3}));
        assert(queen.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem king = items.getItem(Point{4, yRows[i][0]});
        assert(king.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(king.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((king.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 5, yRows[i][1] * 10 + 3, yRows[i][1] * 10 + 4, yRows[i][1] * 10 + 5}));
        assert((king.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3}));
        assert(king.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(king.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem bishopF = items.getItem(Point{5, yRows[i][0]});
        assert(bishopF.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(bishopF.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((bishopF.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 4, yRows[i][1] * 10 + 6}));
        assert((bishopF.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 4}));
        assert(bishopF.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((bishopF.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 7}));

        BoardItem knightG = items.getItem(Point{6, yRows[i][0]});
        assert((knightG.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 5, yRows[i][2] * 10 + 7}));
        assert(knightG.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((knightG.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][1] * 10 + 4}));
        assert((knightG.actions.get(ActionType::SUPPORT).get(ActionRelation::BY) == ActionHashes{yRows[i][0] * 10 + 7}));
        assert(knightG.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(knightG.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem rookH = items.getItem(Point{7, yRows[i][0]});
        assert(rookH.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert(rookH.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert((rookH.actions.get(ActionType::SUPPORT).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 6, yRows[i][1] * 10 + 7}));
        assert(rookH.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert((rookH.actions.get(ActionType::XRAY).get(ActionRelation::TO) == ActionHashes{yRows[i][0] * 10 + 5, yRows[i][6] * 10 + 7}));
        assert(rookH.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnA = items.getItem(Point{0, yRows[i][1]});
        assert((pawnA.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10}));
        assert(pawnA.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnA.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnA.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10}));
        assert(pawnA.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnA.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10}));

        BoardItem pawnB = items.getItem(Point{1, yRows[i][1]});
        assert((pawnB.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 1}));
        assert(pawnB.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnB.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnB.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 2}));
        assert(pawnB.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnB.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnC = items.getItem(Point{2, yRows[i][1]});
        assert((pawnC.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 2}));
        assert(pawnC.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnC.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnC.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 3}));
        assert(pawnC.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnC.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnD = items.getItem(Point{3, yRows[i][1]});
        assert((pawnD.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 3}));
        assert(pawnD.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnD.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnD.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 1, yRows[i][0] * 10 + 2, yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 4}));
        assert(pawnD.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnD.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10 + 3}));

        BoardItem pawnE = items.getItem(Point{4, yRows[i][1]});
        assert((pawnE.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 4}));
        assert(pawnE.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnE.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnE.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 3, yRows[i][0] * 10 + 4, yRows[i][0] * 10 + 5, yRows[i][0] * 10 + 6}));
        assert(pawnE.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnE.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnF = items.getItem(Point{5, yRows[i][1]});
        assert((pawnF.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 5}));
        assert(pawnF.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnF.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnF.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 4}));
        assert(pawnF.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnF.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnG = items.getItem(Point{6, yRows[i][1]});
        assert((pawnG.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 6}));
        assert(pawnG.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnG.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnG.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 5}));
        assert(pawnG.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(pawnG.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem pawnH = items.getItem(Point{7, yRows[i][1]});
        assert((pawnH.actions.get(ActionType::PLACE).get(ActionRelation::TO) == ActionHashes{yRows[i][2] * 10 + 7}));
        assert(pawnH.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
        assert(pawnH.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert((pawnH.actions.get(ActionType::SUPPORT).get(ActionRelation::BY)== ActionHashes{yRows[i][0] * 10 + 7}));
        assert(pawnH.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert((pawnH.actions.get(ActionType::XRAY).get(ActionRelation::BY) == ActionHashes{yRows[i][7] * 10 + 7}));

        BoardItem itemA2 = items.getItem(Point{0, yRows[i][2]});
        assert(itemA2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemA2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10, yRows[i][0] * 10 + 1}));
        assert(itemA2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemA2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemA2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemA2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemB2 = items.getItem(Point{1, yRows[i][2]});
        assert(itemB2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemB2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 1}));
        assert(itemB2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemB2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemB2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemB2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemC2 = items.getItem(Point{2, yRows[i][2]});
        assert(itemC2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemC2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 2, yRows[i][0] * 10 + 1}));
        assert(itemC2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemC2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemC2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemC2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemD2 = items.getItem(Point{3, yRows[i][2]});
        assert(itemD2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemD2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 3}));
        assert(itemD2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemD2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemD2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemD2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemE2 = items.getItem(Point{4, yRows[i][2]});
        assert(itemE2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemE2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 4}));
        assert(itemE2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemE2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemE2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemE2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemF2 = items.getItem(Point{5, yRows[i][2]});
        assert(itemF2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemF2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 5, yRows[i][0] * 10 + 6}));
        assert(itemF2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemF2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemF2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemF2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemG2 = items.getItem(Point{6, yRows[i][2]});
        assert(itemG2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemG2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 6}));
        assert(itemG2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemG2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemG2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemG2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        BoardItem itemH2 = items.getItem(Point{7, yRows[i][2]});
        assert(itemH2.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
        assert((itemH2.actions.get(ActionType::PLACE).get(ActionRelation::BY) == ActionHashes{yRows[i][1] * 10 + 7, yRows[i][0] * 10 + 6}));
        assert(itemH2.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
        assert(itemH2.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
        assert(itemH2.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
        assert(itemH2.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());

        for (int j = 0; j < 8; ++j) {
            BoardItem item = items.getItem(Point{j, yRows[i][3]});
            assert(item.actions.get(ActionType::PLACE).get(ActionRelation::TO).empty());
            assert(item.actions.get(ActionType::PLACE).get(ActionRelation::BY).empty());
            assert(item.actions.get(ActionType::SUPPORT).get(ActionRelation::TO).empty());
            assert(item.actions.get(ActionType::SUPPORT).get(ActionRelation::BY).empty());
            assert(item.actions.get(ActionType::XRAY).get(ActionRelation::TO).empty());
            assert(item.actions.get(ActionType::XRAY).get(ActionRelation::BY).empty());
        }
    }
}

int main() {
    test_direction();
    test_point();
    test_square();
    test_piece();
    test_piece_pack();
    test_board_item_action();
    test_board_item_actions();
    test_board_item();
    test_board_items();
    test_initial_pieces();
    test_initial_actions();

    std::cout << "OK" << std::endl;
}
