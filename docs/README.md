# Docs

## Dependencies

```
Handler
| <- Action
| <- Board
| <- FEN
| <- HistoryMove
| <- State

Action
| <- Point

Board
| <- Direction
| <- Point

FEN
| <- Square
| <- State

HistoryMove
| <- Point

State
| <- Piece
| <- Point

Point
| <- Direction

Piece
| <- Direction
| <- Point
| <- Square

Square
| <- Point
```

## Describtion

- [Action](action)
- [Board](board)
- [Direction](direction)
- [FEN](fen)
- [Handler](handler)
- [State](state)
