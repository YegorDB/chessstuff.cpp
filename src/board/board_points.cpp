#include "board.h"

Board::Points Board::points() {
    return Points{
        Points::Iterator{0},
        Points::Iterator{64},
    };
};

Board::Points::Points(
    Board::Points::Iterator begin,
    Board::Points::Iterator end
) : _begin{begin}, _end{end} {};

Board::Points::Iterator Board::Points::begin() const {
    return _begin;
};

Board::Points::Iterator Board::Points::end() const {
    return _end;
};

Board::Points::Iterator::Iterator(int index) : _index{index}, _point{Point{index % 8, index / 8}} {};

Board::Points::Iterator& Board::Points::Iterator::operator++() {
    nextStep();
    return *this;
};

Point* Board::Points::Iterator::operator*() {
    return &_point;
};

bool Board::Points::Iterator::operator==(const Board::Points::Iterator& other) const {
    return this->_index == other._index;
};

bool Board::Points::Iterator::operator!=(const Board::Points::Iterator& other) const {
    return this->_index != other._index;
};

void Board::Points::Iterator::nextStep() {
    ++_index;
    _point = Point{_index % 8, _index / 8};
};
