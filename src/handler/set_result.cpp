#include "handler.h"

void Handler::_setResult() {
    if (_checkIsCheckmate()) {
        PieceColor winnerColor = _state.activeColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
        _state.result = State::Result {State::Result::Type::CHECKMATE, winnerColor};
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
