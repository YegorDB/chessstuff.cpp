#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();
    testMoveAndPawnPromotion();

    std::cout << "testHandler OK" << std::endl;
};
