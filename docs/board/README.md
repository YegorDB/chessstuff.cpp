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


## Board squares to points mapping

```
X      0     1     2     3     4     5     6     7
     _____ _____ _____ _____ _____ _____ _____ _____
    |     |     |     |     |     |     |     |     |
    | a8  | b8  | c8  | d8  | e8  | f8  | g8  | h8  |  0
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a7  | b7  | c7  | d7  | e7  | f7  | g7  | h7  |  1
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a6  | b6  | c6  | d6  | e6  | f6  | g6  | h6  |  2
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a5  | b5  | c5  | d5  | e5  | f5  | g5  | h5  |  3
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a4  | b4  | c4  | d4  | e4  | f4  | g4  | h4  |  4
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a3  | b3  | c3  | d3  | e3  | f3  | g3  | h3  |  5
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a2  | b2  | c2  | d2  | e2  | f2  | g2  | h2  |  6
    |_____|_____|_____|_____|_____|_____|_____|_____|
    |     |     |     |     |     |     |     |     |
    | a1  | b1  | c1  | d1  | e1  | f1  | g1  | h1  |  7
    |_____|_____|_____|_____|_____|_____|_____|_____|

                                                       Y
```

Diagram shows squares to points mapping.
For exapmle c5 is Point{2, 3}, e2 is Point{4, 6}.
