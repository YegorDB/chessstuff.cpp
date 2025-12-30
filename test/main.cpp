#include <iostream>

#include "action/test_action.h"
#include "board/test_board.h"
#include "direction/test_direction.h"
#include "fen/test_fen.h"
#include "handler/test_handler.h"
#include "history/test_history.h"
#include "piece/test_piece.h"
#include "piece_places/test_piece_places.h"
#include "point/test_point.h"
#include "square/test_square.h"

int main() {
    testAction();
    testBoard();
    testDirection();
    testFen();
    testHandler();
    testHistoryMoves();
    testPiece();
    testPiecePlaces();
    testPoint();
    testSquare();

    std::cout << "OK" << std::endl;
}
