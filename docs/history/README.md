# History


##  Schema

```
HistoryMove
    HistoryMove <- ()
    HistoryMove <- PieceType
                <- Point
                <- Point
                <- HistoryMove::Type
                <- int
                <- bool
                <- PieceType
                <- PointSet
    PIECE_TYPES_TO_SYMBOLS -> std::string
    toString -> std::string

HistoryMoves
    HistoryMoves <- ()
    addMainLineMove <- HistoryMove
    addSideLineMove <- HistoryMove
                    <- int
    toString <- bool
             -> std::string
    getItems -> std::vector<Item>

HistoryMoves::Item
    historyMove <-> HistoryMove
    nextIndexes <-> std::vector<int>
```


## class HistoryMove

> Single chess move information

### PropertiesHistoryMove::

#### static const std::string PIECE_TYPES_TO_SYMBOLS

> Piece types to symbols mapping

#### PieceType pieceType

> Moved piece type

#### Point from

> Point move from

#### Point to

> Point move to

#### HistoryMove::Type type

> Move type

#### int checkersCount

> Checkers count after move

#### bool isCheckMate

> True if there is check mate after move

#### PieceType promotionType

> Pawn promotion piece type

#### PointSet otherCandidates

>  Other same type pieces that could make this move

### Methods

#### HistoryMove::toString() -> const std::string&

> Returns move algebraic notation

### Constructors

#### HistoryMove::HistoryMove()

> Creates empty move

#### HistoryMove::HistoryMove(PieceType pieceType, Point from, Point to, Type type, int checkersCount, bool isCheckMate, PieceType promotionType, PointSet otherCandidates)

> Creates move


## enum class HistoryMove::Type

> Move type

### Values

- PLACE
- TAKE
- PAWN_PROMOTION
- KING_SIDE_CASTLE
- QUEEN_SIDE_CASTLE


## class HistoryMoves

> Chess moves collection. Contains one main line (moves sequence) and could contains several side lines.

### Methods

#### HistoryMoves::addMainLineMove(HistoryMove&& historyMove) -> void

> Add main line move after previous main line move

#### HistoryMoves::addSideLineMove(HistoryMove&& historyMove, int prevItemIndex) -> void

> Add side line move after previous move (main or side) by moves item index

#### HistoryMoves::toString() -> const std::string&

> Returns moves in PGN

#### HistoryMoves::getItems() -> const std::vector<HistoryMoves::Item>&

> Returns moves in PGN

### Constructors

#### HistoryMoves::HistoryMoves()

> Creates empty moves


## struct HistoryMoves::Item

> Moves item

### Properties

#### const HistoryMove historyMove

> Wrapped move

#### std::vector<int> nextIndexes

> Next moves indexes
