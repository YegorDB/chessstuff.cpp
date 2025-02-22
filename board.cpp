#include <stdexcept>

#include "board.h"

Board::Board() {
    _matrix.clear();
    for (int i = 0; i < 8; ++i) {
        _matrix.push_back({});
        for (int j = 0; j < 8; ++j) {
            Square s{j, i};
            Square bi{s};
            _matrix[i].push_back(bi);
        }
    }
};

Board::Squares Board::squares() {
    return Squares{
        Iterator{_matrix, 0},
        Iterator{_matrix, 64},
    };
};

Board::Squares Board::squaresWithPieces() {
    return Squares{
        Iterator{_matrix, 0, &Square::hasPiece},
        Iterator{_matrix, 64, &Square::hasPiece},
    };
};

Board::SquaresByDirection Board::squaresByDirection(const Point& point, const Direction& direction, bool withStartPoint) {
    return SquaresByDirection{
        IteratorWithDitrection{_matrix, point, direction, withStartPoint},
        IteratorWithDitrection{_matrix, Point{8, 8}, direction, true},
    };
};

const Square& Board::getSquare(const Point& point) const {
    return _matrix[point.y()][point.x()];
};

void Board::placePiece(Piece* piece, const Point& to) {
    if (!to.isValid()) {
        throw std::runtime_error{"Invalid point to place a piece."};
    }
    _matrix[to.y()][to.x()].placePiece(piece);
};

Board::Squares::Squares(Board::Iterator begin, Board::Iterator end) : _begin{begin}, _end{end} {
};

Board::Iterator Board::Squares::begin() const {
    return _begin;
};

Board::Iterator Board::Squares::end() const {
    return _end;
};

Board::SquaresByDirection::SquaresByDirection(
    Board::IteratorWithDitrection begin,
    Board::IteratorWithDitrection end
) : _begin{begin}, _end{end} {};

Board::IteratorWithDitrection Board::SquaresByDirection::begin() const {
    return _begin;
};

Board::IteratorWithDitrection Board::SquaresByDirection::end() const {
    return _end;
};

Board::Iterator::Iterator(Matrix& matrix, int index) : _matrix{matrix}, _index{index}, _point{Point{index % 8, index / 8}} {}

Board::Iterator::Iterator(Matrix& matrix, int index, Filter* filter) : Board::Iterator(matrix, index) {
    _filter = filter;
    filterSquares();
}

Board::Iterator& Board::Iterator::operator++() {
    nextStep();
    filterSquares();
    return *this;
}

Square* Board::Iterator::operator*() {
    return &_matrix[_point.y()][_point.x()];
}

bool Board::Iterator::operator==(const Board::Iterator& other) const {
    return this->_index == other._index;
};

bool Board::Iterator::operator!=(const Board::Iterator& other) const {
    return this->_index != other._index;
};

void Board::Iterator::nextStep() {
    ++_index;
    _point = Point{_index % 8, _index / 8};
}

void Board::Iterator::filterSquares() {
    if (_filter == nullptr) return;

    while (_point.isValid() && !(*_filter)(_matrix[_point.y()][_point.x()])) {
        nextStep();
    }
};

Board::IteratorWithDitrection::IteratorWithDitrection(
    Matrix& matrix,
    const Point& point,
    const Direction& direction,
    bool withStartPoint
) : _matrix{matrix}, _point{Point{point.x(), point.y()}}, _direction{direction} {
    if (!withStartPoint) {
        nextStep();
    }
}

Board::IteratorWithDitrection& Board::IteratorWithDitrection::operator++() {
    nextStep();
    return *this;
}

Square* Board::IteratorWithDitrection::operator*() {
    return &_matrix[_point.y()][_point.x()];
}

bool Board::IteratorWithDitrection::operator==(const Board::IteratorWithDitrection& other) const {
    return this->_point == other._point;
};

bool Board::IteratorWithDitrection::operator!=(const Board::IteratorWithDitrection& other) const {
    return !(this->_point == other._point);
};

void Board::IteratorWithDitrection::nextStep() {
    _point = _point.next(_direction);
    ++_distance;
    if (!_point.isValid() || _distance > _direction.maxDistance) {
        _point = Point{8, 8};
    }
};
