#include "test_handler.h"

void testHandler() {
    testInitialActions();
    testInitialPieces();
    testKingRestrictions();

    std::cout << "testHandler OK" << std::endl;
};
