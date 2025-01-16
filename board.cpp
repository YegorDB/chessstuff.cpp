#include "board.h"

Board::Board() {
    initItems();
    initPiecePacks();
    initPieces();

    clearActions();
    setActions();
}

void Board::initItems() {
    items = BoardItems{};
}

void Board::initPiecePacks() {
    piecePacks.clear();
    piecePacks.push_back(PiecePack(true));
    piecePacks.push_back(PiecePack(false));
}

void Board::initOneSidePieces(bool isWhiteColor) {
    int pack = isWhiteColor ? 0 : 1;
    int firstLine = isWhiteColor ? 0 : 7;
    int secondLine = isWhiteColor ? 1 : 6;

    items.placePiece(piecePacks[pack].rooks[0], Point{0, firstLine});
    items.placePiece(piecePacks[pack].knights[0], Point{1, firstLine});
    items.placePiece(piecePacks[pack].bishops[0], Point{2, firstLine});
    items.placePiece(piecePacks[pack].queens[0], Point{3, firstLine});
    items.placePiece(piecePacks[pack].king, Point{4, firstLine});
    items.placePiece(piecePacks[pack].bishops[1], Point{5, firstLine});
    items.placePiece(piecePacks[pack].knights[1], Point{6, firstLine});
    items.placePiece(piecePacks[pack].rooks[1], Point{7, firstLine});
    for (int i = 0; i < 8; ++i) {
        items.placePiece(piecePacks[pack].pawns[i], Point{i, secondLine});
    }
}

void Board::initPieces() {
    initOneSidePieces(true);
    initOneSidePieces(false);
}

const BoardItems& Board::getItems() const {
    return items;
}

void Board::clearActions() {
    for (auto item : items.sequence()) {
        item->actions.clear();
    }
};

void Board::setActions() {
    for (auto item : items.sequenceWithPieces()) {
        for (auto direction : item->piece->getPlaceDirections()) {
            bool after_piece = false;
            for (auto nextItem : items.sequenceByDirection(item->square.point, direction)) {
                if (nextItem->piece == nullptr) {
                    if (after_piece) {
                        item->actions.xray.insertTo(nextItem->square.point.hash());
                        nextItem->actions.xray.insertBy(item->square.point.hash());
                    } else {
                        item->actions.place.insertTo(nextItem->square.point.hash());
                        nextItem->actions.place.insertBy(item->square.point.hash());
                    }
                } else {
                    if (after_piece) {
                        break;
                    }
                    after_piece = true;
                }
            }
        }
        break; // test
    }
};
