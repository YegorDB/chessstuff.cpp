#include "handler.h"

void Handler::_validatePosition() const {
    _validatePiecesCount();
    _validatePawnsPositions();
    _validateKingsThreats();
};

void Handler::_validatePiecesCount() const {
    std::unordered_map<Piece::Color, std::unordered_map<Piece::Type, int>> counter;
    std::unordered_map<Piece::Color, int> aggregatedCounter;

    for (const auto& [point, piece] : _state.piecePlaces.getItems()) {
        counter[piece.getColor()][piece.getType()]++;
        aggregatedCounter[piece.getColor()]++;

        if (aggregatedCounter[piece.getColor()] > 16) {
            throw std::runtime_error{std::format("{} pieces count greater than 16.", piece.isWhiteColor() ? "White" : "Black")};
        }
    }

    for (Piece::Color pieceColor : {Piece::Color::WHITE, Piece::Color::BLACK}) {
        std::string colorName = Piece::COLOR_NAMES[pieceColor == Piece::Color::WHITE ? 0 : 1];

        if (!counter[pieceColor].contains(Piece::Type::KING) || counter[pieceColor][Piece::Type::KING] != 1) {
            throw std::runtime_error{std::format("Incorrect {} kings number.", colorName)};
        }

        if (counter[pieceColor].contains(Piece::Type::QUEEN) && counter[pieceColor][Piece::Type::QUEEN] > 9) {
            throw std::runtime_error{std::format("Incorrect {} queens number.", colorName)};
        }

        if (counter[pieceColor].contains(Piece::Type::ROOK) && counter[pieceColor][Piece::Type::ROOK] > 10) {
            throw std::runtime_error{std::format("Incorrect {} rooks number.", colorName)};
        }

        if (counter[pieceColor].contains(Piece::Type::BISHOP) && counter[pieceColor][Piece::Type::BISHOP] > 10) {
            throw std::runtime_error{std::format("Incorrect {} bishops number.", colorName)};
        }

        if (counter[pieceColor].contains(Piece::Type::KNIGHT) && counter[pieceColor][Piece::Type::KNIGHT] > 10) {
            throw std::runtime_error{std::format("Incorrect {} knights number.", colorName)};
        }

        if (counter[pieceColor].contains(Piece::Type::PAWN) && counter[pieceColor][Piece::Type::PAWN] > 8) {
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
    Piece::Color inactiveColor = _state.activeColor == Piece::Color::WHITE ? Piece::Color::BLACK : Piece::Color::WHITE;
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
