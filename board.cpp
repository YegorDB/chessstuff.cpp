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

BoardItems& Board::getItems() {
    return items;
}

void Board::clearActions() {
    for (auto item : items.sequence()) {
        item->actions.clear();
    }
};

void Board::setActions() {
    for (BoardItem* item : items.sequenceWithPieces()) {
        for (Direction direction : item->piece->getPlaceDirections()) {
            bool after_piece = false;
            for (BoardItem* nextItem : items.sequenceByDirection(item->square.point, direction)) {
                if (nextItem->piece == nullptr) {
                    if (after_piece) {
                        setAction(ActionType::XRAY, item, nextItem);
                    } else {
                        setAction(ActionType::PLACE, item, nextItem);
                    }
                } else {
                    if (after_piece) {
                        setAction(ActionType::XRAY, item, nextItem);
                        break;
                    } else if (item->piece->hasSameColor(nextItem->piece)) {
                        setAction(ActionType::SUPPORT, item, nextItem);
                    } else {
                        setAction(ActionType::THREAT, item, nextItem);
                    }
                    after_piece = true;
                }
            }
        }
        break; // test
    }
};

void Board::setAction(ActionType type, BoardItem* byItem, BoardItem* toItem) {
    byItem->actions.insert(type, ActionRelation::TO, toItem->square);
    toItem->actions.insert(type, ActionRelation::BY, byItem->square);
};
