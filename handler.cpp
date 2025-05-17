#include "handler.h"

Handler::Handler(const FEN& fen) {
    _initPieces(fen);
    _clearActions();
    _setActions();
};

Handler::Handler() : Handler(FEN{FEN::INITIAL_POSITION}) {};

void Handler::_initPieces(const FEN& fen) {
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
    /*
    Active color piece has
    - squares without pieces to place to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to

    Inactive color piece has
    - squares without pieces to threat to
    - squares with opposite color pieces to threat to
    - squares with same color pieces to support to
    - squares with pieces to xray to
    - squares with opposite color pieces to bind to
    */

    std::vector<Square*> bindedSquares;
    _setBaseActions(bindedSquares);
    _restrictKingActions();
};

void Handler::_setBaseActions(std::vector<Square*>& bindedSquares) {
    for (Square* square : _board.squaresWithPieces()) {
        if (square->getPiece().hasColor(_state.activeColor)) {
            for (Direction direction : square->getPiece().getPlaceDirections()) {
                for (Square* nextSquare : _board.squaresByDirection(square->point, direction)) {
                    if (Square::hasPiece(*nextSquare)) {
                        break;
                    }
                    _setAction(ActionType::PLACE, square, nextSquare);
                }
            }
        }
        for (Direction direction : square->getPiece().getThreatDirections()) {
            Square* prevSquare = nullptr;
            Square* prevSquareWithPiece = nullptr;
            for (Square* nextSquare : _board.squaresByDirection(square->point, direction)) {
                if (!Square::hasPiece(*nextSquare)) {
                    if (!square->getPiece().hasColor(_state.activeColor) && prevSquareWithPiece == nullptr) {
                        _setAction(ActionType::THREAT, square, nextSquare);
                    } else {
                        _threatSquareAfterKingIfNeeded(square, prevSquare, nextSquare);
                    }

                    prevSquare = nextSquare;
                    continue;
                }
                if (prevSquareWithPiece != nullptr) {
                    _setAction(ActionType::XRAY, square, nextSquare);
                    _bindPieceIfNeeded(square, prevSquareWithPiece, nextSquare, bindedSquares);
                    _supportPieceAfterKingIfNeeded(square, prevSquareWithPiece, nextSquare);
                    break;
                }
                if (square->hasSameColorPieces(nextSquare)) {
                    _setAction(ActionType::SUPPORT, square, nextSquare);
                } else {
                    _setAction(ActionType::THREAT, square, nextSquare);
                }
                prevSquare = nextSquare;
                prevSquareWithPiece = nextSquare;
            }
        }
    }
};

void Handler::_restrictKingActions() {
    Square* activeKingSquare;
    for (Square* square : _board.squaresWithPieces()) {
        if (square->getPiece().isKing() && square->getPiece().hasColor(_state.activeColor)) {
            activeKingSquare = square;
            break;
        }
    }

    PointSet placeToPointsCopy;
    for (Point point : activeKingSquare->getActions().get(ActionType::PLACE).get(ActionRelation::TO)) {
        placeToPointsCopy.insert(point);
    }

    for (Point point : placeToPointsCopy) {
        const Square nextSquare = _board.getSquare(point);
        if (!nextSquare.getActions().get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
            activeKingSquare->dropAction(ActionType::PLACE, ActionRelation::TO, &nextSquare);
        }
    }

    PointSet threatToPointsCopy;
    for (Point point : activeKingSquare->getActions().get(ActionType::THREAT).get(ActionRelation::TO)) {
        threatToPointsCopy.insert(point);
    }

    for (Point point : threatToPointsCopy) {
        const Square nextSquare = _board.getSquare(point);
        if (!nextSquare.getActions().get(ActionType::SUPPORT).get(ActionRelation::BY).empty()) {
            activeKingSquare->dropAction(ActionType::THREAT, ActionRelation::TO, &nextSquare);
        }
    }
};

void Handler::_setAction(ActionType type, Square* bySquare, Square* toSquare) {
    bySquare->setAction(type, ActionRelation::TO, toSquare);
    toSquare->setAction(type, ActionRelation::BY, bySquare);
};

/**
 * Example:
 * Black queen bind white bishop before white king
 *  _____ _____ _____ _____
 * |    *|     |    *|     |
 * |  Q  |     |  B  |  K  |
 * |_____|_____|_____|_____|
 */
void Handler::_bindPieceIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare, std::vector<Square*>& bindedSquares) {
    bool isPrevSquarePieceHasToBeBinded = (
        nextSquare->getPiece().isKing()
        && nextSquare->hasSameColorPieces(prevSquareWithPiece)
        && !nextSquare->hasSameColorPieces(square)
    );
    if (!isPrevSquarePieceHasToBeBinded) return;

    bindedSquares.push_back(prevSquareWithPiece);
    _setAction(ActionType::BIND, square, prevSquareWithPiece);
};

/**
 * Example:
 * Black rook threat square after white king
 *  _____ _____ _____ _____
 * |    *|     |     |    *|
 * |  r  |     |  K  |     |
 * |_____|_____|_____|_____|
 */
void Handler::_threatSquareAfterKingIfNeeded(Square* square, Square* prevSquare, Square* nextSquare) {
    bool isNextSquareHasToBeThreated = (
        !square->getPiece().hasColor(_state.activeColor)
        && Square::hasPiece(*prevSquare)
        && prevSquare->getPiece().isKing()
        && !square->hasSameColorPieces(prevSquare)
    );
    if (!isNextSquareHasToBeThreated) return;

    _setAction(ActionType::THREAT, square, nextSquare);
};

/**
 * Example:
 * White rook suport white knight after black king
 *  _____ _____ _____ _____
 * |    *|     |     |    *|
 * |  R  |     |  k  |  N  |
 * |_____|_____|_____|_____|
 */
void Handler::_supportPieceAfterKingIfNeeded(Square* square, Square* prevSquareWithPiece, Square* nextSquare) {
    bool isNextSquareHasToBeSupported = (
        !square->getPiece().hasColor(_state.activeColor)
        && prevSquareWithPiece->getPiece().isKing()
        && !prevSquareWithPiece->hasSameColorPieces(square)
        && nextSquare->hasSameColorPieces(square)
    );
    if (!isNextSquareHasToBeSupported) return;

    _setAction(ActionType::SUPPORT, square, nextSquare);
};
