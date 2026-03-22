#include "handler.h"

void Handler::_setResult() {
    State::Result result;
    if (_checkIsCheckmate()) {
        result.type = State::Result::Type::CHECKMATE;
        result.winnerColor = _state.activeColor == Piece::Color::WHITE ? Piece::Color::BLACK : Piece::Color::WHITE;
        _currentHistoryMove.isCheckMate = true;
    } else if (_checkIsStalemate()) {
        result.type = State::Result::Type::DRAW;
        result.drawType = State::Result::DrawType::STALEMATE;
    } else if (_checkIsInsufficientMaterial()) {
        result.type = State::Result::Type::DRAW;
        result.drawType = State::Result::DrawType::INSUFFICIENT_MATERIAL;
    } else if (_checkIsFiftyMoveRule()) {
        result.type = State::Result::Type::DRAW;
        result.drawType = State::Result::DrawType::FIFTY_MOVE_RULE;
    } else if (_checkIsThreefoldRepetition()) {
        result.type = State::Result::Type::DRAW;
        result.drawType = State::Result::DrawType::THREEFOLD_REPETITION;
    }

    if (result.type != State::Result::Type::UNSET) {
        _state.result = result;
    }
};

bool Handler::_checkIsCheckmate() const {
    const Point& kingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    const PointSet kingThreaters = _actionsPlaces.getActions(kingPoint).get(Action::Type::THREAT).get(Action::Relation::BY);

    if (!kingThreaters.empty()) {
        const PointSet kingThreatTo = _actionsPlaces.getActions(kingPoint).get(Action::Type::THREAT).get(Action::Relation::TO);
        const PointSet kingPlaceTo = _actionsPlaces.getActions(kingPoint).get(Action::Type::PLACE).get(Action::Relation::TO);
        if (kingThreatTo.empty() && kingPlaceTo.empty()) {
            if (kingThreaters.size() > 1) {
                return true;
            }
            const Point& threaterPoint = *(kingThreaters.begin());
            const Actions& threaterActions = _actionsPlaces.getActions(threaterPoint);
            if (threaterActions.get(Action::Type::THREAT).get(Action::Relation::BY).empty()) {
                for (Point* p : Board::pointsByTwoPoints(kingPoint, threaterPoint, false, false)) {
                    if (!_actionsPlaces.getActions(*p).get(Action::Type::PLACE).get(Action::Relation::BY).empty()) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    return false;
};

bool Handler::_checkIsStalemate() const {
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (!piece.hasColor(_state.activeColor)) {
            continue;
        }

        const Actions& actions = _actionsPlaces.getActions(point);
        bool hasThreatToAction = !actions.get(Action::Type::THREAT).get(Action::Relation::TO).empty();
        bool hasPlaceToAction = !actions.get(Action::Type::PLACE).get(Action::Relation::TO).empty();
        if (hasThreatToAction || hasPlaceToAction) {
            return false;
        }
    }
    return true;
};

/**
 * Insufficient material:
 * - king vs king
 * - king and bishop vs king
 * - king and knight vs king
 * - king and bishop vs king and bishop (and same color bishops)
 */
bool Handler::_checkIsInsufficientMaterial() const {
    std::unordered_map<Piece::Color, std::unordered_map<Piece::Type, int>> counter;
    std::unordered_map<Piece::Color, int> aggregatedCounter;
    std::unordered_map<Piece::Color, bool> bishopOnLightSquareMap;

    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (
            piece.getType() == Piece::Type::QUEEN
            || piece.getType() == Piece::Type::ROOK
            || piece.getType() == Piece::Type::PAWN
        ) {
            return false;
        }

        counter[piece.getColor()][piece.getType()]++;
        aggregatedCounter[piece.getColor()]++;
        if (piece.isBishop()) {
            Square square{point};
            bishopOnLightSquareMap[piece.getColor()] = square.isLightColor;
        }
    }

    if (aggregatedCounter[Piece::Color::WHITE] > 2 || aggregatedCounter[Piece::Color::BLACK] > 2) {
        return false;
    }
    if (aggregatedCounter[Piece::Color::WHITE] == 2 && aggregatedCounter[Piece::Color::BLACK] == 2) {
        if (counter[Piece::Color::WHITE][Piece::Type::BISHOP] == 0 || counter[Piece::Color::BLACK][Piece::Type::BISHOP] == 0) {
            return false;
        }
        return bishopOnLightSquareMap[Piece::Color::WHITE] == bishopOnLightSquareMap[Piece::Color::BLACK];
    }
    return true;
};

bool Handler::_checkIsFiftyMoveRule() const {
    return _state.halfmoveClock >= 100;
};

bool Handler::_checkIsThreefoldRepetition() const {
    return _maxPositionCount > 2;
};
