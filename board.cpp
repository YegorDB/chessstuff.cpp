#include "board.h"

Board::Board() {
    initItems();
    initPiecePacks();
    initPieces();
}

void Board::initItems() {
    items.clear();
    for (int i = 0; i < 8; ++i) {
        items.push_back({});
        for (int j = 0; j < 8; ++j) {
            Square s{j, i};
            BoardItem bi{s};
            items[i].push_back(bi);
        }
    }
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

    items[firstLine][0].piece = &(piecePacks[pack].rooks[0]);
    items[firstLine][1].piece = &(piecePacks[pack].knights[0]);
    items[firstLine][2].piece = &(piecePacks[pack].bishops[0]);
    items[firstLine][3].piece = &(piecePacks[pack].queens[0]);
    items[firstLine][4].piece = &(piecePacks[pack].king);
    items[firstLine][5].piece = &(piecePacks[pack].bishops[1]);
    items[firstLine][6].piece = &(piecePacks[pack].knights[1]);
    items[firstLine][7].piece = &(piecePacks[pack].rooks[1]);
    for (int i = 0; i < 8; ++i) {
        items[secondLine][i].piece = &(piecePacks[pack].pawns[i]);
    }
}

void Board::initPieces() {
    initOneSidePieces(true);
    initOneSidePieces(false);
}

const BoardItems& Board::getItems() const {
    return items;
}
