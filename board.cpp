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
    for (auto item : items.sequence()) {
        if (item->piece == nullptr) continue;

        for (auto direction : item->piece->getPlaceDirections()) {
            Point nextPoint = item->square.point;
            bool after_piece = false;
            for (int d = 0; d < direction.maxDistance; ++d) {
                nextPoint = nextPoint.next(direction);
                if (!nextPoint.isValid()) break;

                BoardItem nextItem = items.matrix[nextPoint.y()][nextPoint.x()];
                if (nextItem.piece == nullptr) {
                    if (after_piece) {
                        item->actions.xray.insert_to(nextPoint.hash());
                        nextItem.actions.xray.insert_by(item->square.point.hash());
                    } else {
                        item->actions.place.insert_to(nextPoint.hash());
                        nextItem.actions.place.insert_by(item->square.point.hash());
                    }
                } else {
                }
            }
        }
        break; // test
    }
};
