# Point


## Schema

```
Point
    Point <- ()
    Point <- int

    x -> int
    y -> int
    hash -> int
    next <- Direction
         -> Point
    isValid -> bool
    isUndefined -> bool
    toString -> std::string

pointSetToString <- std::unordered_set<Point, PointHasher>
                 -> std::string
```


## class Point

> Chess square point.

### Methods

#### Point::x() -> int

> Returns x coordinate.

#### Point::y() -> int

> Returns y coordinate.

#### Point::hash() -> int

> Returns point hash based on coordinates.

#### Point::next(const Direction& direction) -> Point

> Returns next point according to direction.

#### Point::isValid() -> bool

> Returns true if point is valid.

#### Point::isUndefined() -> bool

> Returns true if point is undefined.

#### Point::toString() -> const std::string

> Returns point string representation.

### Constructors

#### Point::Point(int x, int y))

> Creates point by two coorditanes.

#### Point::Point()

> Creates point with unset coordinates.


## struct PointHasher

> Point hashing logic.


## function pointSetToString(const std::unordered_set<Point, PointHasher>& pointSet) -> const std::string

> Returns point set string representation.
