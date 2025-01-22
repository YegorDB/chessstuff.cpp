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
    BoardItemAction action{};

    action.insertTo(1);

    BoardItemActionHashes toValues = action.getTo();
    assert(toValues.size() == 1);
    assert(toValues.find(1) != toValues.end());

    action.insertBy(2);

    BoardItemActionHashes byValues = action.getBy();
    assert(byValues.size() == 1);
    assert(byValues.find(2) != byValues.end());

    action.clear();

    assert(action.getTo().empty());
    assert(action.getBy().empty());
}

void test_board_item_actions() {
    BoardItemActions actions{};

    actions.getThreat().insertTo(1);
    actions.getThreat().insertBy(11);
    assert(!actions.getThreat().getTo().empty());
    assert(!actions.getThreat().getBy().empty());

    actions.getSupport().insertTo(2);
    actions.getSupport().insertBy(12);
    assert(!actions.getSupport().getTo().empty());
    assert(!actions.getSupport().getBy().empty());

    actions.getPlace().insertTo(3);
    actions.getPlace().insertBy(13);
    assert(!actions.getPlace().getTo().empty());
    assert(!actions.getPlace().getBy().empty());

    actions.getXray().insertTo(4);
    actions.getXray().insertBy(14);
    assert(!actions.getXray().getTo().empty());
    assert(!actions.getXray().getBy().empty());

    actions.clear();

    assert(actions.getThreat().getTo().empty());
    assert(actions.getThreat().getBy().empty());
    assert(actions.getSupport().getTo().empty());
    assert(actions.getSupport().getBy().empty());
    assert(actions.getPlace().getTo().empty());
    assert(actions.getPlace().getBy().empty());
    assert(actions.getXray().getTo().empty());
    assert(actions.getXray().getBy().empty());
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

int main() {
    // Piece k{PieceType::KING, false};
    // std::cout << static_cast<int>(k.type) << " " << k.getColorName() << std::endl;

    // for (auto dd : k.getPlaceDirections()) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    // for (auto dd : k.getThreatDirections()) {
    //     std::cout << dd.dx << " " << dd.dy << " " << dd.maxDistance << std::endl;
    // }

    // Square s4{1, 2};
    // Piece pi{PieceType::KING, false};

    // BoardItem bi{s4, &pi};
    // std::cout << bi.square.toString() << std::endl;

    // Board b{};
    // auto items = b.getItems();

    // int i = 0;
    // for (auto item : items.sequence()) {
    //     std::cout << item->square.getName() << " ";
    //     if (++i % 8 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    // std::cout << std::endl;

    // i = 0;
    // for (auto item : items.sequenceWithPieces()) {
    //     std::cout << item->square.getName() << " ";
    //     if (++i % 8 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    // std::cout << std::endl;

    // std::cout << (items.getItem(Point{3, 2}).piece == nullptr) << std::endl;
    // std::cout << (items.getItem(Point{3, 7}).piece != nullptr) << std::endl;
    // std::cout << (items.getItem(Point{4, 0}).piece != nullptr) << std::endl;

    // std::cout << (items.getItem(Point{4, 0}).piece->type == PieceType::KING) << std::endl;
    // Piece k3 = *items.getItem(Point{4, 0}).piece;
    // std::cout << static_cast<int>(k3.type) << " " << k3.getColorName() << std::endl;

    // std::cout << (items.getItem(Point{3, 7}).piece->type == PieceType::QUEEN) << std::endl;
    // Piece q3 = *items.getItem(Point{3, 7}).piece;
    // std::cout << static_cast<int>(q3.type) << " " << q3.getColorName() << std::endl;

    test_direction();
    test_point();
    test_square();
    test_piece();
    test_piece_pack();
    test_board_item_action();
    test_board_item_actions();
    test_board_item();

    std::cout << "OK" << std::endl;
}
