# Docs

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
