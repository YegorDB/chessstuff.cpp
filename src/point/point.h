#pragma once

#include <string>
#include <unordered_set>

#include "../direction/direction.h"

class Point {
private:
    int _x, _y, _hash;
    bool _undefined = false;

public:
    Point();
    Point(int x, int y);

    void operator=(const Point& point);
    bool operator==(const Point& other) const;

    int x() const;
    int y() const;
    int hash() const;

    Point next(const Direction& direction);
    bool isValid() const;
    bool isUndefined() const;
    const std::string toString() const;
};

struct PointHasher {
    int operator()(const Point& point) const;
};

using PointSet = std::unordered_set<Point, PointHasher>;

const std::string pointSetToString(const PointSet& pointSet);
