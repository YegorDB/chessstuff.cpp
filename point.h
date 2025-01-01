#include <string>

#include "direction.h"

class Point {
private:
    int _x, _y, _hash;

public:
    Point(int x, int y);

    void operator=(Point point);

    int x() const;
    int y() const;
    int hash() const;

    Point next(Direction direction);
    bool isValid();
    const std::string toString() const;
};
