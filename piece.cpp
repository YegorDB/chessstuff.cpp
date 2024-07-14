#include "piece.h"

Piece::Piece(PieceType type, bool isWhiteColor) : type(type), isWhiteColor(isWhiteColor) {
    color = isWhiteColor ? 0 : 1;
    colorName = COLOR_NAMES[color];
}

const std::string& Piece::getColorName() const {
    return colorName;
}
