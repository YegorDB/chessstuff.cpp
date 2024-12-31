#include "board_item.h"

BoardItem::BoardItem(Square square) : square(square) {};

BoardItem::BoardItem(Square square, Piece* piece) : square(square), piece(piece) {};

BoardItems::BoardItems() {
    matrix.clear();
    for (int i = 0; i < 8; ++i) {
        matrix.push_back({});
        for (int j = 0; j < 8; ++j) {
            Square s{j, i};
            BoardItem bi{s};
            matrix[i].push_back(bi);
        }
    }
};

BoardItems::Sequence BoardItems::sequence() {
    return Sequence{
        Iterator{matrix, 0},
        Iterator{matrix, 64},
    };
};

// const BoardItems::Matrix& BoardItems::matrix() const {
//     return _matrix;
// };

BoardItems::Sequence::Sequence(BoardItems::Iterator begin, BoardItems::Iterator end) : _begin{begin}, _end{end} {
};

BoardItems::Iterator BoardItems::Sequence::begin() const {
    return _begin;
};

BoardItems::Iterator BoardItems::Sequence::end() const {
    return _end;
};

BoardItems::Iterator::Iterator(Matrix& matrix, int index) : matrix{matrix}, index{index} {
}

BoardItems::Iterator& BoardItems::Iterator::operator++() {
    ++index;
    return *this;
}

BoardItem* BoardItems::Iterator::operator*() {
    int y = index / 8;
    int x = index % 8;
    return &matrix[y][x];
}

bool BoardItems::Iterator::operator==(const BoardItems::Iterator& other) const {
    return this->index == other.index;
};

bool BoardItems::Iterator::operator!=(const BoardItems::Iterator& other) const {
    return this->index != other.index;
};
