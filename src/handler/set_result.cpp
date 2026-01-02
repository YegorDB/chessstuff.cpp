#include "handler.h"

void Handler::_setResult() {
    State::Result result;
    if (_checkIsCheckmate()) {
        result.type = State::Result::Type::CHECKMATE;
        result.winnerColor = _state.activeColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
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
    }

    if (result.type != State::Result::Type::UNSET) {
        _state.result = result;
    }
};

bool Handler::_checkIsCheckmate() const {
    const Point& kingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    const PointSet kingThreaters = _actionsPlaces.getActions(kingPoint).get(ActionType::THREAT).get(ActionRelation::BY);

    if (!kingThreaters.empty()) {
        const PointSet kingThreatTo = _actionsPlaces.getActions(kingPoint).get(ActionType::THREAT).get(ActionRelation::TO);
        const PointSet kingPlaceTo = _actionsPlaces.getActions(kingPoint).get(ActionType::PLACE).get(ActionRelation::TO);
        if (kingThreatTo.empty() && kingPlaceTo.empty()) {
            if (kingThreaters.size() > 1) {
                return true;
            }
            const Point& threaterPoint = *(kingThreaters.begin());
            const Actions& threaterActions = _actionsPlaces.getActions(threaterPoint);
            if (threaterActions.get(ActionType::THREAT).get(ActionRelation::BY).empty()) {
                for (Point* p : Board::pointsByTwoPoints(kingPoint, threaterPoint, false, false)) {
                    if (!_actionsPlaces.getActions(*p).get(ActionType::PLACE).get(ActionRelation::BY).empty()) {
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
        bool hasThreatToAction = !actions.get(ActionType::THREAT).get(ActionRelation::TO).empty();
        bool hasPlaceToAction = !actions.get(ActionType::PLACE).get(ActionRelation::TO).empty();
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
    std::unordered_map<PieceColor, std::unordered_map<PieceType, int>> counter;
    std::unordered_map<PieceColor, int> aggregatedCounter;
    std::unordered_map<PieceColor, bool> bishopOnLightSquareMap;

    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (
            piece.getType() == PieceType::QUEEN
            || piece.getType() == PieceType::ROOK
            || piece.getType() == PieceType::PAWN
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

    if (aggregatedCounter[PieceColor::WHITE] > 2 || aggregatedCounter[PieceColor::BLACK] > 2) {
        return false;
    }
    if (aggregatedCounter[PieceColor::WHITE] == 2 && aggregatedCounter[PieceColor::BLACK] == 2) {
        if (counter[PieceColor::WHITE][PieceType::BISHOP] == 0 || counter[PieceColor::BLACK][PieceType::BISHOP] == 0) {
            return false;
        }
        return bishopOnLightSquareMap[PieceColor::WHITE] == bishopOnLightSquareMap[PieceColor::BLACK];
    }
    return true;
};

bool Handler::_checkIsFiftyMoveRule() const {
    return _state.halfmoveClock >= 100;
};
