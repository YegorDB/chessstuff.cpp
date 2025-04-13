#include "handler.h"

Handler::Handler() {
    initBoard();
    initPiecePacks();
    initPieces();

    clearActions();
    setActions();
};

void Handler::initBoard() {
    board = Board{};
};

void Handler::initPiecePacks() {
    piecePacks.clear();
    piecePacks.push_back(PiecePack(true));
    piecePacks.push_back(PiecePack(false));
};

void Handler::initOneSidePieces(bool isWhiteColor) {
    int pack = isWhiteColor ? 0 : 1;
    int firstLine = isWhiteColor ? 0 : 7;
    int secondLine = isWhiteColor ? 1 : 6;

    board.placePiece(&piecePacks[pack].rooks[0], Point{0, firstLine});
    board.placePiece(&piecePacks[pack].knights[0], Point{1, firstLine});
    board.placePiece(&piecePacks[pack].bishops[0], Point{2, firstLine});
    board.placePiece(&piecePacks[pack].queens[0], Point{3, firstLine});
    board.placePiece(&piecePacks[pack].king, Point{4, firstLine});
    board.placePiece(&piecePacks[pack].bishops[1], Point{5, firstLine});
    board.placePiece(&piecePacks[pack].knights[1], Point{6, firstLine});
    board.placePiece(&piecePacks[pack].rooks[1], Point{7, firstLine});
    for (int i = 0; i < 8; ++i) {
        board.placePiece(&piecePacks[pack].pawns[i], Point{i, secondLine});
    }
};

void Handler::initPieces() {
    initOneSidePieces(true);
    initOneSidePieces(false);
};

Board& Handler::getBoard() {
    return board;
};

void Handler::clearActions() {
    for (Square* square : board.squares()) {
        square->clearActions();
    }
};

void Handler::setActions() {
    for (Square* square : board.squaresWithPieces()) {
        for (Direction direction : square->getPiece()->getPlaceDirections()) {
            for (Square* nextSquare : board.squaresByDirection(square->point, direction)) {
                if (Square::hasPiece(*nextSquare)) {
                    break;
                }
                setAction(ActionType::PLACE, square, nextSquare);
            }
        }
        for (Direction direction : square->getPiece()->getThreatDirections()) {
            Square* prevSquare = nullptr;
            for (Square* nextSquare : board.squaresByDirection(square->point, direction)) {
                if (!Square::hasPiece(*nextSquare)) {
                    continue;
                }
                if (prevSquare != nullptr) {
                    setAction(ActionType::XRAY, square, nextSquare);
                    if (nextSquare->getPiece()->isKing() && nextSquare->hasSameColorPieces(prevSquare)) {
                        setAction(ActionType::BIND, square, prevSquare);
                    }
                    break;
                }
                if (square->hasSameColorPieces(nextSquare)) {
                    setAction(ActionType::SUPPORT, square, nextSquare);
                } else {
                    setAction(ActionType::THREAT, square, nextSquare);
                }
                prevSquare = nextSquare;
            }
        }
    }
};

void Handler::setAction(ActionType type, Square* bySquare, Square* toSquare) {
    bySquare->setAction(type, ActionRelation::TO, toSquare);
    toSquare->setAction(type, ActionRelation::BY, bySquare);
};
