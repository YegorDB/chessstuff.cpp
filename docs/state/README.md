# State


## Schema

```
State
    piecePlaces <-> PiecePlaces
    activeColor <-> PieceColor
    castles <-> std::unordered_map<PieceColor, CastleSides>
    enPassant <-> Point
    halfmoveClock <-> int
    movesCount <-> int
    pawnPromotion <-> Point
    result <-> State::Result

State::CastleSides
    kingSide <-> bool
    queenSide <-> bool

State::Result
    type <-> State::Result::Type
    winnerColor <-> PieceColor
    drawType <-> State::Result::DrawType
```


## struct State

> Chess game state

### Properties

#### PiecePlaces piecePlaces

> Piece places map

#### PieceColor activeColor

> Active color enum value

#### State::Castles castles

> Castles data

#### Point enPassant

> En passant point

#### int halfmoveClock

> Halfmove clock value

#### int movesCount

> Moves count value

#### Point pawnPromotion

> Pawn promotion point

#### Result result

> Game result


## struct State::CastleSides

> State castle sides data

### Properties

#### bool kingSide

> Is king side castle allowed

#### bool queenSide

> Is queen side castle allowed


## struct State::Result

> Game result data

### Properties

#### State::Result::Type type

> Result type enum value

#### PieceColor winnerColor

> Winner color enum value

#### State::Result::DrawType drawType

> Draw type enum value


## enum class State::Result::Type

> Game result type

### Values

- UNSET
- DRAW
- CHECKMATE


## enum class State::Result::DrawType

> Game result draw type

### Values

- UNSET
- STALEMATE
- INSUFFICIENT_MATERIAL
- THREEFOLD_REPETITION
- FIFTY_MOVE_RULE
