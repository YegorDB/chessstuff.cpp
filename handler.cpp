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

void Handler::initPieces() {
    FEN fen{FEN::INITIAL_POSITION};
    State state = fen.getState();
    for (const auto& [point, pieceInfo] : state.piecePlaces) {
        int pack = pieceInfo.color == PieceColor::WHITE ? 0 : 1;
        board.placePiece(piecePacks[pack].getPiece(pieceInfo.type), point);
    }
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
