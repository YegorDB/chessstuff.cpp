# Tutorial

## Brief view

```c++
Handler handler{};
assert(FEN{handler.getState()}.getRawString() == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

Handler::Response response1 = handler.move(sp("f2"), sp("f3"));
assert(response1.isOk());
assert(FEN{handler.getState()}.getRawString() == "rnbqkbnr/pppppppp/8/8/8/5P2/PPPPP1PP/RNBQKBNR b KQkq - 0 1");
assert(handler.getState().result.type == State::Result::Type::UNSET);

Handler::Response response2 = handler.move(sp("e7"), sp("e5"));
assert(response2.isOk());
assert(FEN{handler.getState()}.getRawString() == "rnbqkbnr/pppp1ppp/8/4p3/8/5P2/PPPPP1PP/RNBQKBNR w KQkq e6 0 2");
assert(handler.getState().result.type == State::Result::Type::UNSET);

Handler::Response response3 = handler.move(sp("g2"), sp("g4"));
assert(response3.isOk());
assert(FEN{handler.getState()}.getRawString() == "rnbqkbnr/pppp1ppp/8/4p3/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq g3 0 2");
assert(handler.getState().result.type == State::Result::Type::UNSET);

Handler::Response response4 = handler.move(sp("d8"), sp("h4"));
assert(response4.isOk());
assert(FEN{handler.getState()}.getRawString() == "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3");
assert(handler.getState().result.type == State::Result::Type::CHECKMATE);
assert(handler.getState().result.winnerColor == Piece::Color::BLACK);
```
