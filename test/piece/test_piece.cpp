#include "test_piece.h"

void testKing() {
    Piece king{PieceType::KING, false};
    assert(static_cast<int>(king.getType()) == 1);
    assert(king.getColorName() == "black");
    assert(king.getPlaceDirections() == king.getThreatDirections());
    assert(king.getMovesCount() == 0);
    assert(king.getVisibleSymbol() == "\u265A");
    assert(king.hasColor(PieceColor::BLACK));
    assert(king.hasSameColor(Piece{PieceType::PAWN, false}));
    assert(king.isKing());
    assert(!king.isQueen());
    assert(!king.isRook());
    assert(!king.isBishop());
    assert(!king.isKnight());
    assert(!king.isPawn());
    assert(!king.isUndefined());
    assert((king.getPlaceDirections()[0] == Direction{-1, -1}));
    assert((king.getPlaceDirections()[1] == Direction{0, -1}));
    assert((king.getPlaceDirections()[2] == Direction{1, -1}));
    assert((king.getPlaceDirections()[3] == Direction{-1, 0}));
    assert((king.getPlaceDirections()[4] == Direction{1, 0}));
    assert((king.getPlaceDirections()[5] == Direction{-1, 1}));
    assert((king.getPlaceDirections()[6] == Direction{0, 1}));
    assert((king.getPlaceDirections()[7] == Direction{1, 1}));

    king.increaseMovesCount();
    assert(king.getMovesCount() == 1);
};

void testQueen() {
    Piece queen{PieceType::QUEEN, true};
    assert(static_cast<int>(queen.getType()) == 2);
    assert(queen.getColorName() == "white");
    assert(queen.getPlaceDirections() == queen.getThreatDirections());
    assert(queen.getMovesCount() == 0);
    assert(queen.getVisibleSymbol() == "\u2655");
    assert(queen.hasColor(PieceColor::WHITE));
    assert(queen.hasSameColor(Piece{PieceType::KING, true}));
    assert(!queen.isKing());
    assert(queen.isQueen());
    assert(!queen.isRook());
    assert(!queen.isBishop());
    assert(!queen.isKnight());
    assert(!queen.isPawn());
    assert(!queen.isUndefined());
    assert((queen.getPlaceDirections()[0] == Direction{-1, -1, 7}));
    assert((queen.getPlaceDirections()[1] == Direction{0, -1, 7}));
    assert((queen.getPlaceDirections()[2] == Direction{1, -1, 7}));
    assert((queen.getPlaceDirections()[3] == Direction{-1, 0, 7}));
    assert((queen.getPlaceDirections()[4] == Direction{1, 0, 7}));
    assert((queen.getPlaceDirections()[5] == Direction{-1, 1, 7}));
    assert((queen.getPlaceDirections()[6] == Direction{0, 1, 7}));
    assert((queen.getPlaceDirections()[7] == Direction{1, 1, 7}));
};

void testRook() {
    Piece rook{PieceType::ROOK, false};
    assert(static_cast<int>(rook.getType()) == 3);
    assert(rook.getColorName() == "black");
    assert(rook.getMovesCount() == 0);
    assert(rook.getVisibleSymbol() == "\u265C");
    assert(rook.hasColor(PieceColor::BLACK));
    assert(rook.hasSameColor(Piece{PieceType::QUEEN, false}));
    assert(!rook.isKing());
    assert(!rook.isQueen());
    assert(rook.isRook());
    assert(!rook.isBishop());
    assert(!rook.isKnight());
    assert(!rook.isPawn());
    assert(!rook.isUndefined());
    assert(rook.getPlaceDirections() == rook.getThreatDirections());
    assert((rook.getPlaceDirections()[0] == Direction{0, -1, 7}));
    assert((rook.getPlaceDirections()[1] == Direction{-1, 0, 7}));
    assert((rook.getPlaceDirections()[2] == Direction{1, 0, 7}));
    assert((rook.getPlaceDirections()[3] == Direction{0, 1, 7}));
};

void testBishop() {
    Piece bishop{PieceType::BISHOP, true};
    assert(static_cast<int>(bishop.getType()) == 4);
    assert(bishop.getColorName() == "white");
    assert(bishop.getMovesCount() == 0);
    assert(bishop.getVisibleSymbol() == "\u2657");
    assert(bishop.hasColor(PieceColor::WHITE));
    assert(bishop.hasSameColor(Piece{PieceType::ROOK, true}));
    assert(!bishop.isKing());
    assert(!bishop.isQueen());
    assert(!bishop.isRook());
    assert(bishop.isBishop());
    assert(!bishop.isKnight());
    assert(!bishop.isPawn());
    assert(!bishop.isUndefined());
    assert(bishop.getPlaceDirections() == bishop.getThreatDirections());
    assert((bishop.getPlaceDirections()[0] == Direction{-1, -1, 7}));
    assert((bishop.getPlaceDirections()[1] == Direction{1, -1, 7}));
    assert((bishop.getPlaceDirections()[2] == Direction{-1, 1, 7}));
    assert((bishop.getPlaceDirections()[3] == Direction{1, 1, 7}));
};

void testKnight() {
    Piece knight{PieceType::KNIGHT, false};
    assert(static_cast<int>(knight.getType()) == 5);
    assert(knight.getColorName() == "black");
    assert(knight.getMovesCount() == 0);
    assert(knight.getVisibleSymbol() == "\u265E");
    assert(knight.hasColor(PieceColor::BLACK));
    assert(knight.hasSameColor(Piece{PieceType::BISHOP, false}));
    assert(!knight.isKing());
    assert(!knight.isQueen());
    assert(!knight.isRook());
    assert(!knight.isBishop());
    assert(knight.isKnight());
    assert(!knight.isPawn());
    assert(!knight.isUndefined());
    assert(knight.getPlaceDirections() == knight.getThreatDirections());
    assert((knight.getPlaceDirections()[0] == Direction{-1, -2}));
    assert((knight.getPlaceDirections()[1] == Direction{1, -2}));
    assert((knight.getPlaceDirections()[2] == Direction{-2, -1}));
    assert((knight.getPlaceDirections()[3] == Direction{2, -1}));
    assert((knight.getPlaceDirections()[4] == Direction{-2, 1}));
    assert((knight.getPlaceDirections()[5] == Direction{2, 1}));
    assert((knight.getPlaceDirections()[6] == Direction{-1, 2}));
    assert((knight.getPlaceDirections()[7] == Direction{1, 2}));
};

void testPawn() {
    Piece pawn1{PieceType::PAWN, true};
    assert(static_cast<int>(pawn1.getType()) == 6);
    assert(pawn1.getColorName() == "white");
    assert(pawn1.getMovesCount() == 0);
    assert(pawn1.getVisibleSymbol() == "\u2659");
    assert(pawn1.hasColor(PieceColor::WHITE));
    assert(pawn1.hasSameColor(Piece{PieceType::KNIGHT, true}));
    assert(!pawn1.isKing());
    assert(!pawn1.isQueen());
    assert(!pawn1.isRook());
    assert(!pawn1.isBishop());
    assert(!pawn1.isKnight());
    assert(pawn1.isPawn());
    assert(!pawn1.isUndefined());
    assert(pawn1.getPlaceDirections() != pawn1.getThreatDirections());
    assert((pawn1.getPlaceDirections()[0] == Direction{0, -1}));
    assert((pawn1.getThreatDirections()[0] == Direction{-1, -1}));
    assert((pawn1.getThreatDirections()[1] == Direction{1, -1}));

    Piece pawn2{PieceType::PAWN, false};
    assert(static_cast<int>(pawn2.getType()) == 6);
    assert(pawn2.getColorName() == "black");
    assert(pawn2.getMovesCount() == 0);
    assert(pawn2.getVisibleSymbol() == "\u265F");
    assert(pawn2.hasColor(PieceColor::BLACK));
    assert(pawn2.hasSameColor(Piece{PieceType::KNIGHT, false}));
    assert(!pawn2.isKing());
    assert(!pawn2.isQueen());
    assert(!pawn2.isRook());
    assert(!pawn2.isBishop());
    assert(!pawn2.isKnight());
    assert(pawn2.isPawn());
    assert(!pawn2.isUndefined());
    assert(pawn2.getPlaceDirections() != pawn2.getThreatDirections());
    assert((pawn2.getPlaceDirections()[0] == Direction{0, 1}));
    assert((pawn2.getThreatDirections()[0] == Direction{-1, 1}));
    assert((pawn2.getThreatDirections()[1] == Direction{1, 1}));

    assert(!pawn1.hasSameColor(pawn2));
};

void testPieceThrowErrors() {
    assert_error_was_thrown(
        [](){
            (Piece{PieceType::UNSET, true}).getVisibleSymbol();
        },
        "There is no visible symbol to unset piece."
    );

    assert_error_was_thrown(
        [](){
            (Piece{}).getVisibleSymbol();
        },
        "There is no visible symbol to unset piece."
    );
};

void testPiece() {
    testKing();
    testQueen();
    testRook();
    testBishop();
    testKnight();
    testPawn();
    testPieceThrowErrors();

    std::cout << "testPiece OK" << std::endl;
};
