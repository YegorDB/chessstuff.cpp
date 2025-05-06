#include "test_board.h"

void testBoard() {
    Board board{};

    int i = 0;
    for (Square* square : board.squares()) {
        assert(!Square::hasPiece(*square));
        assert((square->point == Point{i % 8, i / 8}));
        ++i;
    }
    assert(i == 64);

    i = 0;
    for (Square* square : board.squaresWithPieces()) {
        ++i;
    }
    assert(i == 0);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7}, true)) {
        assert((square->point == Point{1 + i, 2 + i}));
        ++i;
    }
    assert(i == 6);

    i = 0;
    for (Square* square : board.squaresByDirection(Point{1, 2}, Direction{1, 1, 7})) {
        ++i;
        assert((square->point == Point{1 + i, 2 + i}));
    }
    assert(i == 5);

    Point piecePoint{5, 3};
    Piece king{PieceType::KING, true};
    board.placePiece(king, piecePoint);

    i = 0;
    for (Square* square : board.squaresWithPieces()) {
        assert(Square::hasPiece(*square));
        assert(square->getPiece().isKing());
        assert(square->getPiece().isWhiteColor());
        assert(square->point == piecePoint);
        ++i;
    }
    assert(i == 1);

    Square squareWithPiece = board.getSquare(piecePoint);
    assert(Square::hasPiece(squareWithPiece));
    assert(squareWithPiece.getPiece().isKing());
    assert(squareWithPiece.getPiece().isWhiteColor());

    Square squareWithoutPiece = board.getSquare(Point{1, 2});
    assert(!Square::hasPiece(squareWithoutPiece));

    std::cout << "testBoard OK" << std::endl;
};
