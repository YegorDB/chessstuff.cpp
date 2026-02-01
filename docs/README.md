# Docs

```
Handler
    move -> Handler::Response
    promotePawn -> Handler::Response
    getActionsPlaces -> ActionsPlaces
    getHistoryMoves -> HistoryMoves
    getMaxPositionCount -> int
    getPositionCounts -> PositionCounts
    getState -> State

Handler::Response
    status -> Handler::Response::Status
    isOk -> bool

FEN
    INITIAL_POSITION -> std::string
    getRawString -> std::string
    getRawStringParts -> std::vector<std::string>
    getState -> State

State
    piecePlaces -> PiecePlaces
    activeColor -> PieceColor
    castles -> std::unordered_map<PieceColor, CastleSides>
    enPassant -> Point
    halfmoveClock -> int
    movesCount -> int
    pawnPromotion -> Point
    result -> State::Result

State::CastleSides
    kingSide -> bool
    queenSide -> bool

State::Result
    type -> State::Result::Type
    winnerColor -> PieceColor
    drawType -> State::Result::DrawType
```

## class Handler

> Contains main logic to works with chess position and piece moves

### Methods

#### Handler::move(const Point& from, const Point& to) -> Handler::Response

> Moves piece by two points

#### Handler::promotePawn(PieceType pieceType) -> Handler::Response

> Select pawn promotion piece type

#### Handler::getActionsPlaces() -> const ActionsPlaces&

> Get current action places

#### Handler::getState() -> const State&

> Get current state

#### Handler::getHistoryMoves() -> const HistoryMoves&

> Get current history moves

#### Handler::getPositionCounts() -> const PositionCounts&

> Get current position to repeats count map

#### Handler::getMaxPositionCount() -> int

> Get current max position repeats count

### Constructors

#### Handler::Handler(const FEN& fen)

> Creates handler instance by arbitrary FEN position

#### Handler::Handler()

> Creates handler instance by FEN::INITIAL_POSITION


## class Handler::Response

> Handler interaction response

### Properties

#### const Handler::Response::Status status

> Response status, enum value 

### Methods

#### Handler::Response::isOk() -> bool

> Returns true if response status equals to Handler::Response::Status::OK

### Constructors

#### Handler::Response::Response(Status status)

> Creates response instance by status


## enum class Handler::Response::Status

> Handler interaction response status

### Values

- OK
- INVALID_POINT
- PIECE_DOES_NOT_EXIST
- WRONG_PIECE_COLOR
- WRONG_DESTINATION
- WRONG_PAWN_PROMOTION
- WRONG_PAWN_PROMOTION_PIECE_TYPE
- RESULT_REACHED


## class FEN

> Transform FEN strings to State and vice versa

### Properties

#### static const std::string INITIAL_POSITION

> Classical chess initial position FEN string

### Methods

#### FEN::getRawString() -> const std::string&

> Returns FEN string

#### FEN::getRawStringParts() -> const std::vector<std::string>&

> Returns FEN string parts

#### FEN::getState() -> const State&

> Returns State

### Constructors

#### FEN::FEN(const std::string& rawString)

> Creates instance by FEN string

#### FEN::FEN(const State& state)

> Creates instance by state


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
