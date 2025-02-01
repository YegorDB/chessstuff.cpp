#include "board.h"
#include <cassert>
#include <iostream>

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

void test_board() {
    Board board{};

    int i = 0;
    for (BoardItem* item : board.getItems().sequence()) {
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
    test_board();

    std::cout << "OK" << std::endl;
}
