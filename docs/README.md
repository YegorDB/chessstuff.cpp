# Docs

## Dependencies

```
Handler
| <- Action
| <- Board
| <- FEN
| <- History
| <- State

Action
| <- Point

Board
| <- Direction
| <- Point

FEN
| <- Square
| <- State

History
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
- [History](history)
- [State](state)
