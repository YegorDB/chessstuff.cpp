#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();
    testMove();

    std::cout << "testHandler OK" << std::endl;
};
