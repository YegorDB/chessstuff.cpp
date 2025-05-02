#include "test_fen.h"

void testFenStringToState() {
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
};

void testFenStringToStateTwoKings() {
    FEN fen{"4k3/8/8/8/8/8/8/4K3 b - - 0 0"};

    State s = fen.getState();

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Point point{x, y};
            if (point == Point{4, 0}) {
                assert(s.piecePlaces.at(point).color == PieceColor::BLACK);
                assert(s.piecePlaces.at(point).type == PieceType::KING);
            } else if (point == Point{4, 7}) {
                assert(s.piecePlaces.at(point).color == PieceColor::WHITE);
                assert(s.piecePlaces.at(point).type == PieceType::KING);
            } else {
                assert(!s.piecePlaces.contains(point));
            }
        }
    }

    assert(s.activeColor == PieceColor::BLACK);

    assert(s.castles.whiteKingSide == false);
    assert(s.castles.whiteQueenSide == false);
    assert(s.castles.blackKingSide== false);
    assert(s.castles.blackQueenSide == false);

    assert(s.enPassant == (Point{8, 8}));

    assert(s.halfmoveClock == 0);

    assert(s.movesCount == 0);
};

void testStateToFenString() {
    State s{
        PiecePlaces{
            {Point{0, 0}, PieceInfo{PieceColor::BLACK, PieceType::ROOK}},
            {Point{1, 0}, PieceInfo{PieceColor::BLACK, PieceType::KNIGHT}},
            {Point{2, 0}, PieceInfo{PieceColor::BLACK, PieceType::BISHOP}},
            {Point{3, 0}, PieceInfo{PieceColor::BLACK, PieceType::QUEEN}},
            {Point{4, 0}, PieceInfo{PieceColor::BLACK, PieceType::KING}},
            {Point{5, 0}, PieceInfo{PieceColor::BLACK, PieceType::BISHOP}},
            {Point{6, 0}, PieceInfo{PieceColor::BLACK, PieceType::KNIGHT}},
            {Point{7, 0}, PieceInfo{PieceColor::BLACK, PieceType::ROOK}},
            {Point{0, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{1, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{2, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{3, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{4, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{5, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{6, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{7, 1}, PieceInfo{PieceColor::BLACK, PieceType::PAWN}},
            {Point{0, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{1, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{2, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{3, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{4, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{5, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{6, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{7, 6}, PieceInfo{PieceColor::WHITE, PieceType::PAWN}},
            {Point{0, 7}, PieceInfo{PieceColor::WHITE, PieceType::ROOK}},
            {Point{1, 7}, PieceInfo{PieceColor::WHITE, PieceType::KNIGHT}},
            {Point{2, 7}, PieceInfo{PieceColor::WHITE, PieceType::BISHOP}},
            {Point{3, 7}, PieceInfo{PieceColor::WHITE, PieceType::QUEEN}},
            {Point{4, 7}, PieceInfo{PieceColor::WHITE, PieceType::KING}},
            {Point{5, 7}, PieceInfo{PieceColor::WHITE, PieceType::BISHOP}},
            {Point{6, 7}, PieceInfo{PieceColor::WHITE, PieceType::KNIGHT}},
            {Point{7, 7}, PieceInfo{PieceColor::WHITE, PieceType::ROOK}},
        },
        PieceColor::WHITE,
        State::Castles{true, true, true, true},
        Point{4, 5},
        10,
        15
    };

    FEN fen{s};

    assert(fen.getRawString() == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e3 10 15");
}

void testStateToFenStringTwoKings() {
    State s{
        PiecePlaces{
            {Point{4, 0}, PieceInfo{PieceColor::BLACK, PieceType::KING}},
            {Point{4, 7}, PieceInfo{PieceColor::WHITE, PieceType::KING}},
        },
        PieceColor::BLACK,
        State::Castles{false, false, false, false},
        Point{8, 8},
        0,
        0
    };

    FEN fen{s};

    assert(fen.getRawString() == "4k3/8/8/8/8/8/8/4K3 b - - 0 0");
}

void testFen() {
    testFenStringToState();
    testFenStringToStateTwoKings();
    testStateToFenString();
    testStateToFenStringTwoKings();

    std::cout << "testFen OK" << std::endl;
}
