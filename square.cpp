#include <stdexcept>

#include "square.h"

const std::string Square::COLUMN_SIGNS{"abcdefgh"};
const std::string Square::ROW_SIGNS{"012345678"};
const std::vector<std::string> Square::COLOR_NAMES{"light", "dark"};

Point Square::nameToPoint(const std::string& name) {
    if (name.size() != 2 || name[0] < 97 || name[0] > 104 || name[1] < 49 || name[1] > 56) {
        throw std::runtime_error{"Wrong square name."};
    }
    return Point{name[0] - 97, 56 - name[1]};
};

bool Square::hasPiece(const Square& square) {
    return square.getPiece().getType() != PieceType::UNSET;
};

Square::Square(const Point& p) : point(p), isLightColor(p.x() % 2 == p.y() % 2) {
    _name = {COLUMN_SIGNS[p.x()], ROW_SIGNS[8 - p.y()]};
};

Square::Square(int x, int y) : Square(Point{x, y}) {};

Square::Square(const std::string& name) : Square(nameToPoint(name)) {};

const std::string& Square::getName() const {
    return _name;
};

const std::string& Square::getColorName() const {
    return COLOR_NAMES[isLightColor ? 0 : 1];
};

const Piece& Square::getPiece() const {
    return _piece;
};

const std::string Square::toString() const {
    return _name + " " + point.toString() + " " + getColorName();
};

bool Square::hasSameColorPieces(const Square* other) const {
    return Square::hasPiece(*this) && Square::hasPiece(*other) && _piece.hasSameColor(other->getPiece());
};

void Square::placePiece(const Piece& piece) {
    _piece = piece;
};
