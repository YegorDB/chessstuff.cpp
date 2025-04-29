#include "test_fen.h"

void testFen() {
    FEN fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e3 10 15"};

    State s = fen.getState();

    for (bool isWhiteColor : {true, false}) {
        int firstRowY = isWhiteColor ? 7 : 0;
        int secondRowY = isWhiteColor ? 6 : 1;
        PieceColor pieceColor = isWhiteColor ? PieceColor::WHITE : PieceColor::BLACK;

        for (int x = 0; x < 8; ++x) {
            assert(s.piecePlaces.at(Point{x, firstRowY}).color == pieceColor);
            assert(s.piecePlaces.at(Point{x, secondRowY}).color == pieceColor);
            assert(s.piecePlaces.at(Point{x, secondRowY}).type == PieceType::PAWN);
        }

        assert(s.piecePlaces.at(Point{0, firstRowY}).type == PieceType::ROOK);
        assert(s.piecePlaces.at(Point{1, firstRowY}).type == PieceType::KNIGHT);
        assert(s.piecePlaces.at(Point{2, firstRowY}).type == PieceType::BISHOP);
        assert(s.piecePlaces.at(Point{3, firstRowY}).type == PieceType::QUEEN);
        assert(s.piecePlaces.at(Point{4, firstRowY}).type == PieceType::KING);
        assert(s.piecePlaces.at(Point{5, firstRowY}).type == PieceType::BISHOP);
        assert(s.piecePlaces.at(Point{6, firstRowY}).type == PieceType::KNIGHT);
        assert(s.piecePlaces.at(Point{7, firstRowY}).type == PieceType::ROOK);
    }

    for (int y = 2; y < 6; ++y) {
        for (int x = 0; x < 8; ++x) {
            assert(!s.piecePlaces.contains(Point{x, y}));
        }
    }

    assert(s.activeColor == PieceColor::WHITE);

    assert(s.castles.whiteKingSide == true);
    assert(s.castles.whiteQueenSide == true);
    assert(s.castles.blackKingSide== true);
    assert(s.castles.blackQueenSide == true);

    assert(s.enPassant == (Point{4, 5}));

    assert(s.halfmoveClock == 10);

    assert(s.movesCount == 15);

    std::cout << "testFen OK" << std::endl;
};
