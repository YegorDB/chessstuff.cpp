#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "piece.h"
#include "point.h"

class Square {
private:
    static const std::string COLUMN_SIGNS;
    static const std::string ROW_SIGNS;
    static const std::vector<std::string> COLOR_NAMES;

    std::string _name;
    Piece _piece;

public:
    static bool hasPiece(const Square& square);
    static Point nameToPoint(const std::string& name);

    const Point point;
    const bool isLightColor;

    Square(const Point& point);
    Square(int x, int y);
    Square(const std::string& name);

    const std::string& getName() const;
    const std::string& getColorName() const;
    const Piece& getPiece() const;
    const std::string toString() const;
    bool hasSameColorPieces(const Square* other) const;

    void placePiece(const Piece& piece);
};
