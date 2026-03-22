# Piece


## Schema

```
Piece
    Piece <- ()
    Piece <- Piece::Type
          <- bool

    increaseMovesCount -> void
    getType -> Piece::Type
    getColor -> Piece::Color
    getPlaceDirections -> std::vector<Direction>
    getThreatDirections -> std::vector<Direction>
    getColorName -> std::string
    getVisibleSymbol -> std::string
    getMovesCount -> int
    isWhiteColor -> bool
    hasColor <- Piece::Color
             -> bool
    hasSameColor <- Piece
                 -> bool
    hasSameType <- Piece
                -> bool
    isKing -> bool
    isQueen -> bool
    isRook -> bool
    isBishop -> bool
    isKnight -> bool
    isPawn -> bool
    isUndefined -> bool

PiecePlaces
    PiecePlaces <- ()
    PiecePlaces <- std::unordered_map<Point, Piece, PointHasher>

    getItems -> std::unordered_map<Point, Piece, PointHasher>
    getPiece <- Point
             -> Piece
    getKingPoint <- Piece::Color
                 -> Point
    contains <- Point
             -> bool
    place <- Point
          <- Piece
          -> void
    move <- Point
         <- Piece
         -> void
    remove <- Point
           -> void
```

## class Piece

> Chess piece

### Properties

#### static const std::vector<std::string> COLOR_NAMES

> Piece color names

#### static const std::unordered_map<char, std::pair<Piece::Type, Color>> SYMBOLS_TO_INFO

> Piece symbol to piece info map

#### static const std::unordered_map<char, Piece::Color> SYMBOLS_TO_COLOR

> Piece color symbol to piece color enum map

#### static const std::unordered_map<Piece::Color, std::unordered_map<Type, char>> INFO_TO_SYMBOLS

> Piece color enum and type enum to piece symbol map

#### static const std::unordered_map<Piece::Color, char> COLOR_TO_SYMBOLS

> Piece color enum to piece color symbol map

#### static const std::unordered_set<Piece::Type> PAWN_PROMOTION_TYPES

> Pawn promotion piece types

### Methods

#### Piece::increaseMovesCount() -> void

> Increases piece moves count

#### Piece::getType() -> const Piece::Type 

> Returns piece type enum

#### Piece::getColor() -> const Piece::Color 

> Returns piece color enum

#### Piece::getPlaceDirections() -> const std::vector<Direction>&

> Returns piece place directions

#### Piece::getThreatDirections() -> const std::vector<Direction>&

> Returns piece threat directions

#### Piece::getColorName() -> const std::string&

> Returns piece color name

#### Piece::getVisibleSymbol() -> const std::string&

> Returns piece visible symbol

#### Piece::getMovesCount() -> int

> Returns piece moves count

#### Piece::isWhiteColor() -> bool

> Returns true if piece has white color

#### Piece::hasColor(Piece::Color color) -> bool

> Returns true if piece has particular color

#### Piece::hasSameColor(const Piece& other) -> bool

> Returns true if piece has the same color with other piece

#### Piece::hasSameType(const Piece& other) -> bool

> Returns true if piece has the same type with other piece

#### Piece::isKing() -> bool

> Returns true if piece is king

#### Piece::isQueen() -> bool

> Returns true if piece is queen

#### Piece::isRook() -> bool

> Returns true if piece is rook

#### Piece::isBishop() -> bool

> Returns true if piece is bishop

#### Piece::isKnight() -> bool

> Returns true if piece is knight

#### Piece::isPawn() -> bool

> Returns true if piece is pawn

#### Piece::isUndefined() -> bool

> Returns true if piece is undefined

### Constructors

#### Piece::Piece(Type type, bool isWhiteColor)

> Creates piece with particular type and color

#### Piece::Piece()

> Creates piece with unset type and color


## enum class Piece::Color

> Chess piece color

### Values

- UNSET
- WHITE
- BLACK


## enum class Piece::Type

> Chess piece type

### Values

- UNSET
- KING
- QUEEN
- ROOK
- BISHOP
- KNIGHT
- PAWN


## class PiecePlaces

> Chess pieces and squares (by points) interactions logic

### Methods

#### PiecePlaces::getItems() -> const std::unordered_map<Point, Piece, PointHasher>&

> Returns point to piece map

#### PiecePlaces::getPiece(const Point& point) -> const Piece&

> Returns piece by point

#### PiecePlaces::getKingPoint(Piece::Color color) -> const Point&

> Returns king point by color

#### PiecePlaces::contains(const Point& point) -> bool

> Returns true if there is a piece on the square (check by point)

#### PiecePlaces::place(const Point& point, const Piece& piece) -> void

> Place piece to square by point

#### PiecePlaces::move(const Point& from, const Point& to) -> void

> Move piece by two points

#### PiecePlaces::remove(const Point& point) -> void

> Remove piece by point

### Constructors

#### PiecePlaces::PiecePlaces(const std::unordered_map<Point, Piece, PointHasher>& items)

> Creates pieces and squares interactions logic by points to piece map

#### PiecePlaces::PiecePlaces()

> Creates empty pieces and squares interactions logic
