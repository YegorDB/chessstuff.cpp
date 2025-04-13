#include <iostream>

#include "action/test_action.h"
#include "board/test_board.h"
#include "direction/test_direction.h"
#include "handler/test_handler.h"
#include "piece/test_piece.h"
#include "piece_pack/test_piece_pack.h"
#include "piece_places/test_piece_places.h"
#include "point/test_point.h"
#include "square/test_square.h"

int main() {
    testAction();
    testBoard();
    testDirection();
    testHandler();
    testPiece();
    testPiecePack();
    testPiecePlaces();
    testPoint();
    testSquare();

    std::cout << "OK" << std::endl;
}
