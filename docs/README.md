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

Piece
| <- Direction
| <- Point
| <- Square

Point
| <- Direction

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
- [Piece](piece)
- [Point](point)
- [Square](square)
- [State](state)
