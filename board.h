#pragma once

#include "square.h"

class Board {
using Matrix = std::vector<std::vector<Square>>;
using Filter = bool(const Square&);

private:
    Matrix _matrix;

public:
    class Iterator {
    private:
        Matrix& _matrix;
        int _index;
        Filter* _filter = nullptr;
        Point _point;
        void nextStep();
        void filterSquares();
    public:
        Iterator(Matrix& matrix, int index);
        Iterator(Matrix& matrix, int index, Filter* filter);
        Iterator& operator++();
        Square* operator*();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    class IteratorWithDitrection {
    private:
        Matrix& _matrix;
        Point _point;
        Direction _direction;
        int _distance = 0;
        void nextStep();
    public:
        IteratorWithDitrection(Matrix& matrix, const Point& point, const Direction& direction, bool withStartPoint = false);
        IteratorWithDitrection& operator++();
        Square* operator*();
        bool operator==(const IteratorWithDitrection& other) const;
        bool operator!=(const IteratorWithDitrection& other) const;
    };

    class Squares {
    private:
        Iterator _begin, _end;
    public:
        Squares(Iterator begin, Iterator end);
        Iterator begin() const;
        Iterator end() const;
    };

    class SquaresByDirection {
    private:
        IteratorWithDitrection _begin, _end;
    public:
        SquaresByDirection(IteratorWithDitrection begin, IteratorWithDitrection end);
        IteratorWithDitrection begin() const;
        IteratorWithDitrection end() const;
    };

    Board();
    Squares squares();
    Squares squaresWithPieces();
    SquaresByDirection squaresByDirection(const Point& point, const Direction& direction, bool withStartPoint = false);

    const Square& getSquare(const Point& point) const;
    void placePiece(const Piece& piece, const Point& point);
};
