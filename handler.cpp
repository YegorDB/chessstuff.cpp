#include "handler.h"

Handler::Handler() {
    _initPieces();
    _clearActions();
    _setActions();
};

void Handler::_initPieces() {
    FEN fen{FEN::INITIAL_POSITION};
    State state = fen.getState();
    for (const auto& [point, piece] : state.piecePlaces) {
        _board.placePiece(piece, point);
    }
};

Board& Handler::getBoard() {
    return _board;
};

const State& Handler::getState() {
    _state.piecePlaces = _board.getPiecePlaces();
    return _state;
};

void Handler::_clearActions() {
    for (Square* square : _board.squares()) {
        square->clearActions();
    }
};

void Handler::_setActions() {
    for (Square* square : _board.squaresWithPieces()) {
        for (Direction direction : square->getPiece().getPlaceDirections()) {
            for (Square* nextSquare : _board.squaresByDirection(square->point, direction)) {
                if (Square::hasPiece(*nextSquare)) {
                    break;
                }
                _setAction(ActionType::PLACE, square, nextSquare);
            }
        }
        for (Direction direction : square->getPiece().getThreatDirections()) {
            Square* prevSquare = nullptr;
            for (Square* nextSquare : _board.squaresByDirection(square->point, direction)) {
                if (!Square::hasPiece(*nextSquare)) {
                    continue;
                }
                if (prevSquare != nullptr) {
                    _setAction(ActionType::XRAY, square, nextSquare);
                    if (nextSquare->getPiece().isKing() && nextSquare->hasSameColorPieces(prevSquare)) {
                        _setAction(ActionType::BIND, square, prevSquare);
                    }
                    break;
                }
                if (square->hasSameColorPieces(nextSquare)) {
                    _setAction(ActionType::SUPPORT, square, nextSquare);
                } else {
                    _setAction(ActionType::THREAT, square, nextSquare);
                }
                prevSquare = nextSquare;
            }
        }
    }
};

void Handler::_setAction(ActionType type, Square* bySquare, Square* toSquare) {
    bySquare->setAction(type, ActionRelation::TO, toSquare);
    toSquare->setAction(type, ActionRelation::BY, bySquare);
};
