#include "handler.h"

Handler::Handler() {
    initBoard();
    initPiecePacks();
    initPieces();

    clearActions();
    setActions();
}

void Handler::initBoard() {
    board = Board{};
}

void Handler::initPiecePacks() {
    piecePacks.clear();
    piecePacks.push_back(PiecePack(true));
    piecePacks.push_back(PiecePack(false));
}

void Handler::initOneSidePieces(bool isWhiteColor) {
    int pack = isWhiteColor ? 0 : 1;
    int firstLine = isWhiteColor ? 0 : 7;
    int secondLine = isWhiteColor ? 1 : 6;

    board.placePiece(piecePacks[pack].rooks[0], Point{0, firstLine});
    board.placePiece(piecePacks[pack].knights[0], Point{1, firstLine});
    board.placePiece(piecePacks[pack].bishops[0], Point{2, firstLine});
    board.placePiece(piecePacks[pack].queens[0], Point{3, firstLine});
    board.placePiece(piecePacks[pack].king, Point{4, firstLine});
    board.placePiece(piecePacks[pack].bishops[1], Point{5, firstLine});
    board.placePiece(piecePacks[pack].knights[1], Point{6, firstLine});
    board.placePiece(piecePacks[pack].rooks[1], Point{7, firstLine});
    for (int i = 0; i < 8; ++i) {
        board.placePiece(piecePacks[pack].pawns[i], Point{i, secondLine});
    }
}

void Handler::initPieces() {
    initOneSidePieces(true);
    initOneSidePieces(false);
}

Board& Handler::getBoard() {
    return board;
}

void Handler::clearActions() {
    for (auto item : board.sequence()) {
        item->actions.clear();
    }
};

void Handler::setActions() {
    for (BoardItem* item : board.sequenceWithPieces()) {
        for (Direction direction : item->piece->getPlaceDirections()) {
            for (BoardItem* nextItem : board.sequenceByDirection(item->square.point, direction)) {
                if (nextItem->piece != nullptr) {
                    break;
                }
                setAction(ActionType::PLACE, item, nextItem);
            }
        }
        for (Direction direction : item->piece->getThreatDirections()) {
            BoardItem* prevItem = nullptr;
            for (BoardItem* nextItem : board.sequenceByDirection(item->square.point, direction)) {
                if (nextItem->piece == nullptr) {
                    continue;
                }
                if (prevItem != nullptr) {
                    setAction(ActionType::XRAY, item, nextItem);
                    if (nextItem->piece->type == PieceType::KING && nextItem->piece->hasSameColor(prevItem->piece)) {
                        setAction(ActionType::BIND, item, prevItem);
                    }
                    break;
                }
                if (item->piece->hasSameColor(nextItem->piece)) {
                    setAction(ActionType::SUPPORT, item, nextItem);
                } else {
                    setAction(ActionType::THREAT, item, nextItem);
                }
                prevItem = nextItem;
            }
        }
    }
};

void Handler::setAction(ActionType type, BoardItem* byItem, BoardItem* toItem) {
    byItem->actions.insert(type, ActionRelation::TO, toItem->square);
    toItem->actions.insert(type, ActionRelation::BY, byItem->square);
};
