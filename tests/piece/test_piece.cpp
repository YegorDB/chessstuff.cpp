#include "test_piece.h"

void testKing() {
    Piece king{PieceType::KING, false};
    assert(static_cast<int>(king.getType()) == 1);
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
};

void testQueen() {
    Piece queen{PieceType::QUEEN, true};
    assert(static_cast<int>(queen.getType()) == 2);
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
};

void testRook() {
    Piece rook{PieceType::ROOK, false};
    assert(static_cast<int>(rook.getType()) == 3);
    assert(rook.getColorName() == "black");
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
    assert(pawn1.getPlaceDirections() != pawn1.getThreatDirections());
    assert((pawn1.getPlaceDirections()[0] == Direction{0, -1}));
    assert((pawn1.getThreatDirections()[0] == Direction{-1, -1}));
    assert((pawn1.getThreatDirections()[1] == Direction{1, -1}));

    Piece pawn2{PieceType::PAWN, false};
    assert(static_cast<int>(pawn2.getType()) == 6);
    assert(pawn2.getColorName() == "black");
    assert(pawn2.getPlaceDirections() != pawn2.getThreatDirections());
    assert((pawn2.getPlaceDirections()[0] == Direction{0, 1}));
    assert((pawn2.getThreatDirections()[0] == Direction{-1, 1}));
    assert((pawn2.getThreatDirections()[1] == Direction{1, 1}));

    assert(!pawn1.hasSameColor(&pawn2));
};

void testPiece() {
    testKing();
    testQueen();
    testRook();
    testBishop();
    testKnight();
    testPawn();

    std::cout << "testPiece OK" << std::endl;
};
