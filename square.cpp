#include "square.h"

const std::string Square::COLUMN_SIGNS{"abcdefgh"};
const std::string Square::ROW_SIGNS{"012345678"};
const std::vector<std::string> Square::COLOR_NAMES{"light", "dark"};

Square::Square(Point p, Piece* piece) : point(p), isLightColor(p.x() % 2 == p.y() % 2), _piece(piece) {
    _name = {COLUMN_SIGNS[p.x()], ROW_SIGNS[8 - p.y()]};
}

Square::Square(int x, int y, Piece* piece) : Square(Point{x, y}, piece) {}

Square::Square(std::string name, Piece* piece) : Square(name[0] - 97, 56 - name[1], piece) {}

const std::string& Square::getName() const {
    return _name;
}

const std::string& Square::getColorName() const {
    return COLOR_NAMES[isLightColor ? 0 : 1];
}

const Piece* Square::getPiece() const {
    return _piece;
}

const Actions& Square::getActions() const {
    return _actions;
};

const std::string Square::toString() const {
    return _name + " " + point.toString() + " " + getColorName();
}

bool Square::hasSameColorPieces(Square* other) const {
    return Square::hasPiece(*this) && Square::hasPiece(*other) && _piece->hasSameColor(other->getPiece());
};

void Square::setAction(ActionType type, ActionRelation relation, Square* other) {
    _actions.insert(type, relation, other->point);
};

void Square::clearActions() {
    _actions.clear();
};

void Square::placePiece(Piece* piece) {
    _piece = piece;
};

bool Square::hasPiece(const Square& square) {
    return square.getPiece() != nullptr;
};
