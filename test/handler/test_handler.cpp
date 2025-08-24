#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();
    testBindedWithKingPiecesRestrictions();
    testMoveAndPawnPromotion();
    testPawnJumpMove();
    testPawnEnPassant();

    std::cout << "testHandler OK" << std::endl;
};
