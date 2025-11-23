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

    std::cout << "testHandler OK" << std::endl;
};
