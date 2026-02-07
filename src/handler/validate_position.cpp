#include "handler.h"

void Handler::_validatePosition() const {
    _validatePiecesCount();
    _validatePawnsPositions();
    _validateKingsThreats();
};

void Handler::_validatePiecesCount() const {
    std::unordered_map<PieceColor, std::unordered_map<PieceType, int>> counter;
    std::unordered_map<PieceColor, int> aggregatedCounter;

    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        counter[piece.getColor()][piece.getType()]++;
        aggregatedCounter[piece.getColor()]++;

        if (aggregatedCounter[piece.getColor()] > 16) {
            throw std::runtime_error{std::format("{} pieces count greater than 16.", piece.isWhiteColor() ? "White" : "Black")};
        }
    }

    for (PieceColor pieceColor : {PieceColor::WHITE, PieceColor::BLACK}) {
        std::string colorName = Piece::COLOR_NAMES[pieceColor == PieceColor::WHITE ? 0 : 1];

        if (!counter[pieceColor].contains(PieceType::KING) || counter[pieceColor][PieceType::KING] != 1) {
            throw std::runtime_error{std::format("Incorrect {} kings number.", colorName)};
        }

        if (counter[pieceColor].contains(PieceType::QUEEN) && counter[pieceColor][PieceType::QUEEN] > 9) {
            throw std::runtime_error{std::format("Incorrect {} queens number.", colorName)};
        }

        if (counter[pieceColor].contains(PieceType::ROOK) && counter[pieceColor][PieceType::ROOK] > 10) {
            throw std::runtime_error{std::format("Incorrect {} rooks number.", colorName)};
        }

        if (counter[pieceColor].contains(PieceType::BISHOP) && counter[pieceColor][PieceType::BISHOP] > 10) {
            throw std::runtime_error{std::format("Incorrect {} bishops number.", colorName)};
        }

        if (counter[pieceColor].contains(PieceType::KNIGHT) && counter[pieceColor][PieceType::KNIGHT] > 10) {
            throw std::runtime_error{std::format("Incorrect {} knights number.", colorName)};
        }

        if (counter[pieceColor].contains(PieceType::PAWN) && counter[pieceColor][PieceType::PAWN] > 8) {
            throw std::runtime_error{std::format("Incorrect {} pawns number.", colorName)};
        }
    }
};

void Handler::_validatePawnsPositions() const {
    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        if (piece.isPawn() && _isPawnOnFirstRow(point, piece.isWhiteColor())) {
            throw std::runtime_error{std::format("Pawn on first row at {}.", Square(point).getName())};
        }
    }
};

void Handler::_validateKingsThreats() const {
    PieceColor inactiveColor = _state.activeColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
    const Point& inactiveColorKingPoint = _state.piecePlaces.getKingPoint(inactiveColor);

    const Point& activeColorKingPoint = _state.piecePlaces.getKingPoint(_state.activeColor);
    const PointSet activeColorKingThreaters = _actionsPlaces.getActions(activeColorKingPoint).get(Action::Type::THREAT).get(Action::Relation::BY);
    if (activeColorKingThreaters.contains(inactiveColorKingPoint)) {
        throw std::runtime_error{"Kingns threat each other."};
    }

    const PointSet inactiveColorKingThreaters = _actionsPlaces.getActions(inactiveColorKingPoint).get(Action::Type::THREAT).get(Action::Relation::BY);
    if (!inactiveColorKingThreaters.empty()) {
        throw std::runtime_error{"Inactive king was threated."};
    }
};

bool Handler::_isPawnOnFirstRow(const Point& point, bool isWhiteColor) const {
    return isWhiteColor && point.y() == 7 || !isWhiteColor && point.y() == 0;
};
