#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();
    testBindedWithKingPiecesRestrictions();
    testRestrictActionsOnKingCheck();
    testMoveAndPawnPromotion();
    testPawnJumpMove();
    testPawnEnPassant();
    testCastle();
    testValidatePosition();
    testSetResult();

    std::cout << "testHandler OK" << std::endl;
};
