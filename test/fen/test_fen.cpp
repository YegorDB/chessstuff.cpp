#include "test_fen.h"

void testFenStringToState() {
    FEN fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e3 10 15"};

    assert(fen.getRawStringParts() == (std::vector<std::string>{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", "w", "KQkq", "e3", "10", "15"}));

    State s = fen.getState();

    for (bool isWhiteColor : {true, false}) {
        int firstRowY = isWhiteColor ? 7 : 0;
        int secondRowY = isWhiteColor ? 6 : 1;

        for (int x = 0; x < 8; ++x) {
            assert(s.piecePlaces.getPiece(Point{x, firstRowY}).isWhiteColor() == isWhiteColor);
            assert(s.piecePlaces.getPiece(Point{x, secondRowY}).isWhiteColor() == isWhiteColor);
            assert(s.piecePlaces.getPiece(Point{x, secondRowY}).getType() == PieceType::PAWN);
        }

        assert(s.piecePlaces.getPiece(Point{0, firstRowY}).getType() == PieceType::ROOK);
        assert(s.piecePlaces.getPiece(Point{1, firstRowY}).getType() == PieceType::KNIGHT);
        assert(s.piecePlaces.getPiece(Point{2, firstRowY}).getType() == PieceType::BISHOP);
        assert(s.piecePlaces.getPiece(Point{3, firstRowY}).getType() == PieceType::QUEEN);
        assert(s.piecePlaces.getPiece(Point{4, firstRowY}).getType() == PieceType::KING);
        assert(s.piecePlaces.getPiece(Point{5, firstRowY}).getType() == PieceType::BISHOP);
        assert(s.piecePlaces.getPiece(Point{6, firstRowY}).getType() == PieceType::KNIGHT);
        assert(s.piecePlaces.getPiece(Point{7, firstRowY}).getType() == PieceType::ROOK);
    }

    for (int y = 2; y < 6; ++y) {
        for (int x = 0; x < 8; ++x) {
            assert(!s.piecePlaces.contains(Point{x, y}));
        }
    }

    assert(s.activeColor == PieceColor::WHITE);

    assert(s.castles[PieceColor::WHITE].kingSide == true);
    assert(s.castles[PieceColor::WHITE].queenSide == true);
    assert(s.castles[PieceColor::BLACK].kingSide == true);
    assert(s.castles[PieceColor::BLACK].queenSide == true);

    assert(s.enPassant == (Point{4, 5}));

    assert(s.halfmoveClock == 10);

    assert(s.movesCount == 15);
};

void testFenStringToStateTwoKings() {
    FEN fen{"4k3/8/8/8/8/8/8/4K3 b - - 0 0"};

    assert(fen.getRawStringParts() == (std::vector<std::string>{"4k3/8/8/8/8/8/8/4K3", "b", "-", "-", "0", "0"}));

    State s = fen.getState();

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Point point{x, y};
            if (point == Point{4, 0}) {
                assert(!s.piecePlaces.getPiece(point).isWhiteColor());
                assert(s.piecePlaces.getPiece(point).getType() == PieceType::KING);
            } else if (point == Point{4, 7}) {
                assert(s.piecePlaces.getPiece(point).isWhiteColor());
                assert(s.piecePlaces.getPiece(point).getType() == PieceType::KING);
            } else {
                assert(!s.piecePlaces.contains(point));
            }
        }
    }

    assert(s.activeColor == PieceColor::BLACK);

    assert(s.castles[PieceColor::WHITE].kingSide == false);
    assert(s.castles[PieceColor::WHITE].queenSide == false);
    assert(s.castles[PieceColor::BLACK].kingSide == false);
    assert(s.castles[PieceColor::BLACK].queenSide == false);

    assert(s.enPassant == (Point{}));

    assert(s.halfmoveClock == 0);

    assert(s.movesCount == 0);
};

void testStateToFenString() {
    State s{
        PiecePlaces{
            PiecePlaces::Items{
                {Point{0, 0}, Piece{PieceType::ROOK, false}},
                {Point{1, 0}, Piece{PieceType::KNIGHT, false}},
                {Point{2, 0}, Piece{PieceType::BISHOP, false}},
                {Point{3, 0}, Piece{PieceType::QUEEN, false}},
                {Point{4, 0}, Piece{PieceType::KING, false}},
                {Point{5, 0}, Piece{PieceType::BISHOP, false}},
                {Point{6, 0}, Piece{PieceType::KNIGHT, false}},
                {Point{7, 0}, Piece{PieceType::ROOK, false}},
                {Point{0, 1}, Piece{PieceType::PAWN, false}},
                {Point{1, 1}, Piece{PieceType::PAWN, false}},
                {Point{2, 1}, Piece{PieceType::PAWN, false}},
                {Point{3, 1}, Piece{PieceType::PAWN, false}},
                {Point{4, 1}, Piece{PieceType::PAWN, false}},
                {Point{5, 1}, Piece{PieceType::PAWN, false}},
                {Point{6, 1}, Piece{PieceType::PAWN, false}},
                {Point{7, 1}, Piece{PieceType::PAWN, false}},
                {Point{0, 6}, Piece{PieceType::PAWN, true}},
                {Point{1, 6}, Piece{PieceType::PAWN, true}},
                {Point{2, 6}, Piece{PieceType::PAWN, true}},
                {Point{3, 6}, Piece{PieceType::PAWN, true}},
                {Point{4, 6}, Piece{PieceType::PAWN, true}},
                {Point{5, 6}, Piece{PieceType::PAWN, true}},
                {Point{6, 6}, Piece{PieceType::PAWN, true}},
                {Point{7, 6}, Piece{PieceType::PAWN, true}},
                {Point{0, 7}, Piece{PieceType::ROOK, true}},
                {Point{1, 7}, Piece{PieceType::KNIGHT, true}},
                {Point{2, 7}, Piece{PieceType::BISHOP, true}},
                {Point{3, 7}, Piece{PieceType::QUEEN, true}},
                {Point{4, 7}, Piece{PieceType::KING, true}},
                {Point{5, 7}, Piece{PieceType::BISHOP, true}},
                {Point{6, 7}, Piece{PieceType::KNIGHT, true}},
                {Point{7, 7}, Piece{PieceType::ROOK, true}},
            }
        },
        PieceColor::WHITE,
        State::Castles{
            {PieceColor::WHITE, {true, true}},
            {PieceColor::BLACK, {true, true}}
        },
        Point{4, 5},
        10,
        15
    };

    FEN fen{s};

    assert(fen.getRawString() == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e3 10 15");
    assert(fen.getRawStringParts() == (std::vector<std::string>{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", "w", "KQkq", "e3", "10", "15"}));
}

void testStateToFenStringTwoKings() {
    State s{
        PiecePlaces{
            PiecePlaces::Items{
                {Point{4, 0}, Piece{PieceType::KING, false}},
                {Point{4, 7}, Piece{PieceType::KING, true}},
            }
        },
        PieceColor::BLACK,
        State::Castles{
            {PieceColor::WHITE, {false, false}},
            {PieceColor::BLACK, {false, false}}
        },
        Point{},
        0,
        0
    };

    FEN fen{s};

    assert(fen.getRawString() == "4k3/8/8/8/8/8/8/4K3 b - - 0 0");
    assert(fen.getRawStringParts() == (std::vector<std::string>{"4k3/8/8/8/8/8/8/4K3", "b", "-", "-", "0", "0"}));
}

void testFen() {
    testFenStringToState();
    testFenStringToStateTwoKings();
    testStateToFenString();
    testStateToFenStringTwoKings();

    std::cout << "testFen OK" << std::endl;
}
