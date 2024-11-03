#include <string>

class Point {
public:
    const int x, y;

    Point(int x, int y);

    Point next(int dx, int dy);
    bool isValid();
    const std::string toString() const;
};
