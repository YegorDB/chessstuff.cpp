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

    items.matrix[firstLine][0].piece = &(piecePacks[pack].rooks[0]);
    items.matrix[firstLine][1].piece = &(piecePacks[pack].knights[0]);
    items.matrix[firstLine][2].piece = &(piecePacks[pack].bishops[0]);
    items.matrix[firstLine][3].piece = &(piecePacks[pack].queens[0]);
    items.matrix[firstLine][4].piece = &(piecePacks[pack].king);
    items.matrix[firstLine][5].piece = &(piecePacks[pack].bishops[1]);
    items.matrix[firstLine][6].piece = &(piecePacks[pack].knights[1]);
    items.matrix[firstLine][7].piece = &(piecePacks[pack].rooks[1]);
    for (int i = 0; i < 8; ++i) {
        items.matrix[secondLine][i].piece = &(piecePacks[pack].pawns[i]);
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
            int x = item->square.point.x;
            int y = item->square.point.y;
            int _x = x;
            int _y = y;
            bool after_piece = false;
            for (int d = 0; d < direction.maxDistance; ++d) {
                _x += direction.dx;
                _y += direction.dy;
                if (_x < 0 || _x > 7 || _y < 0 || _y > 7) break;
                if (items.matrix[_y][_x].piece == nullptr) {
                    if (after_piece) {
                        item->actions.xray.insert_to(_y * 10 + _x);
                        items.matrix[_y][_x].actions.xray.insert_by(y * 10 + x);
                    } else {
                        item->actions.place.insert_to(_y * 10 + _x);
                        items.matrix[_y][_x].actions.place.insert_by(y * 10 + x);
                    }
                } else {
                }
            }
        }
        break; // test
    }
};
