#include <stdexcept>

#include "board_item.h"

BoardItem::BoardItem(Square square) : square(square) {};

BoardItem::BoardItem(Square square, Piece* piece) : square(square), piece(piece) {};

bool BoardItem::hasPiece(const BoardItem& item) {
    return item.piece != nullptr;
};

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

BoardItems::Sequence BoardItems::sequenceWithPieces() {
    return Sequence{
        Iterator{matrix, 0, &BoardItem::hasPiece},
        Iterator{matrix, 64, &BoardItem::hasPiece},
    };
};

BoardItems::SequenceByDirection BoardItems::sequenceByDirection(const Point& point, const Direction& direction) {
    return SequenceByDirection{
        IteratorWithDitrection{matrix, point, direction},
        IteratorWithDitrection{matrix, Point{8, 8}, direction},
    };
};

// const BoardItems::Matrix& BoardItems::matrix() const {
//     return _matrix;
// };

void BoardItems::placePiece(Piece& piece, const Point& to) {
    if (!to.isValid()) {
        throw std::runtime_error{"Invalid point to place a piece."};
    }
    matrix[to.y()][to.x()].piece = &piece;
};

BoardItems::Sequence::Sequence(BoardItems::Iterator begin, BoardItems::Iterator end) : _begin{begin}, _end{end} {
};

BoardItems::Iterator BoardItems::Sequence::begin() const {
    return _begin;
};

BoardItems::Iterator BoardItems::Sequence::end() const {
    return _end;
};

BoardItems::SequenceByDirection::SequenceByDirection(
    BoardItems::IteratorWithDitrection begin,
    BoardItems::IteratorWithDitrection end
) : _begin{begin}, _end{end} {};

BoardItems::IteratorWithDitrection BoardItems::SequenceByDirection::begin() const {
    return _begin;
};

BoardItems::IteratorWithDitrection BoardItems::SequenceByDirection::end() const {
    return _end;
};

BoardItems::Iterator::Iterator(Matrix& matrix, int index) : _matrix{matrix}, _index{index}, _point{Point{index % 8, index / 8}} {}

BoardItems::Iterator::Iterator(Matrix& matrix, int index, Filter* filter) : BoardItems::Iterator(matrix, index) {
    _filter = filter;
}

BoardItems::Iterator& BoardItems::Iterator::operator++() {
    while (_index < 64) {
        ++_index;
        _point = Point{_index % 8, _index / 8};
        if (!_point.isValid() || _filter == nullptr) break;

        BoardItem item = _matrix[_point.y()][_point.x()];
        if ((*_filter)(item)) break;
    }
    return *this;
}

BoardItem* BoardItems::Iterator::operator*() {
    return &_matrix[_point.y()][_point.x()];
}

bool BoardItems::Iterator::operator==(const BoardItems::Iterator& other) const {
    return this->_index == other._index;
};

bool BoardItems::Iterator::operator!=(const BoardItems::Iterator& other) const {
    return this->_index != other._index;
};

BoardItems::IteratorWithDitrection::IteratorWithDitrection(
    Matrix& matrix,
    const Point& point,
    const Direction& direction,
    bool withStartPoint
) : _matrix{matrix}, _point{Point{point.x(), point.y()}}, _direction{direction} {
    if (!withStartPoint) {
        nextStep();
    }
}

BoardItems::IteratorWithDitrection& BoardItems::IteratorWithDitrection::operator++() {
    nextStep();
    return *this;
}

BoardItem* BoardItems::IteratorWithDitrection::operator*() {
    return &_matrix[_point.y()][_point.x()];
}

bool BoardItems::IteratorWithDitrection::operator==(const BoardItems::IteratorWithDitrection& other) const {
    return this->_point == other._point;
};

bool BoardItems::IteratorWithDitrection::operator!=(const BoardItems::IteratorWithDitrection& other) const {
    return !(this->_point == other._point);
};

void BoardItems::IteratorWithDitrection::nextStep() {
    _point = _point.next(_direction);
    ++_distance;
    if (!_point.isValid() || _distance > _direction.maxDistance) {
        _point = Point{8, 8};
    }
};
