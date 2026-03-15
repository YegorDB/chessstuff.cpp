# Square


## Schema

```
Square
    Square <- Point
    Square <- int
           <- int
    Square <- std::string

    nameToPoint <- std::string
                -> Point
    point -> Point
    isLightColor -> bool
    getName -> std::string
    getFile -> char
    getRank -> char
    getColorName -> std::string
    toString -> std::string

sp <- std::string
   -> Point
```

## class Square

> Chess board square

### Properties

#### const Point point

> Square point

#### const bool isLightColor

> Returns true if square is light color

### Methods

#### static Square::nameToPoint(const std::string& name) -> Point

> Make point from square name. For example `"e2"` should be `Point(4, 6)`.

#### Square::getName() -> const std::string&

> Returns square name.

#### Square::getFile() -> const char

> Returns square name file.

#### Square::getRank() -> const char

> Returns square name rank.

#### Square::getColorName() -> const std::string&

> Returns square color name.

#### Square::toString() -> const std::string

> Convert Square to string.

### Constructors

#### Square::Square(const Point& point)

> Creates square from point.

#### Square::Square(int x, int y)

> Creates square from point parts.

#### Square::Square(const std::string& name)

> Creates square from name.

## function sp(const std::string& name) -> Point

> Shortest form to make point from square name.
