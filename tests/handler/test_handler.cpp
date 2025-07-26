#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();
    testBindedWithKingPiecesRestrictions();
    testMoveAndPawnPromotion();

    std::cout << "testHandler OK" << std::endl;
};
