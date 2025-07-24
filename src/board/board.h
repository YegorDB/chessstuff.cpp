#pragma once

#include "../point/point.h"

class Board {
public:

    class Points {
    public:
        class Iterator {
        private:
            int _index;
            Point _point;
            void nextStep();
        public:
            Iterator(int index);
            Iterator& operator++();
            Point* operator*();
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        };

        Points(Iterator begin, Iterator end);
        Iterator begin() const;
        Iterator end() const;
    private:
        Iterator _begin, _end;
    };

    class PointsByDirection {
    public:
        class Iterator {
        private:
            Point _point;
            Direction _direction;
            int _distance = 0;
            void nextStep();
        public:
            Iterator(const Point& point, const Direction& direction, bool withStartPoint = false);
            Iterator& operator++();
            Point* operator*();
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        };
        PointsByDirection(Iterator begin, Iterator end);
        Iterator begin() const;
        Iterator end() const;
    private:
        Iterator _begin, _end;
    };

    static Points points();
    static PointsByDirection pointsByDirection(
        const Point& point,
        const Direction& direction,
        bool withStartPoint = false
    );
    static PointsByDirection pointsByTwoPoints(
        const Point& firstPoint,
        const Point& secondPoint
    );
};
