# Board


## Schema

```
Board
    points -> Board::Points
    pointsByDirection -> Board::PointsByDirection
    pointsByTwoPoints -> Board::PointsByDirection

Board::Points
    Board::Points <- Board::Points::Iterator
    begin -> Board::Points::Iterator
    end -> Board::Points::Iterator

Board::Points::Iterator
    Board::Points::Iterator <- int

Board::PointsByDirection
    Board::PointsByDirection <- Board::PointsByDirection::Iterator
    begin -> Board::PointsByDirection::Iterator
    end -> Board::PointsByDirection::Iterator

Board::PointsByDirection::Iterator
    Board::PointsByDirection::Iterator <- Point
                                       <- Direction
                                       <- bool
```


## class Board

> Logic to iterate over points

### Methods

#### static points() -> Board::Points

> Create iteration over all board points

#### static pointsByDirection(const Point& point, const Direction& direction, bool withStartPoint = false) -> Board::PointsByDirection

> Create iteration over points by start point and direction

#### static pointsByTwoPoints(const Point& firstPoint, const Point& secondPoint, bool withStartPoint = false, bool withEndPoint = false) -> Board::PointsByDirection

> Create iteration over points by start point and end point


## class Board::Points

> Iteration over all board points

### Methods

#### begin() -> Board::Points::Iterator

> Returns begin iterator

#### end() -> Board::Points::Iterator

> Returns end iterator

### Constructors

#### Board::Points(Board::Points::Iterator begin, Board::Points::Iterator end)

> Creates iteration over all board points


## class Board::Points::Iterator

> All board points iterator

### Constructors

#### Board::Points::Iterator(int index)

> Creates all board points iterator


## class Board::PointsByDirection

> Iteration over board points by specific direction

### Methods

#### begin() -> Board::PointsByDirection::Iterator

> Returns begin iterator

#### end() -> Board::PointsByDirection::Iterator

> Returns end iterator

### Constructors

#### Board::PointsByDirection(Board::PointsByDirection::Iterator begin, Board::PointsByDirection::Iterator end)

> Creates iteration over board points by specific direction


## class Board::PointsByDirection::Iterator

> Board points by specific direction iterator

### Constructors

#### Board::PointsByDirection::Iterator(const Point& point, const Direction& direction, bool withStartPoint = false)

> Creates board points by specific direction iterator
