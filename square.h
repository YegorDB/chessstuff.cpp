#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "action.h"
#include "piece.h"
#include "point.h"

class Square {
private:
    static const std::string COLUMN_SIGNS;
    static const std::string ROW_SIGNS;
    static const std::vector<std::string> COLOR_NAMES;

    std::string _name;
    Piece _piece;
    Actions _actions;

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
    const Actions& getActions() const;
    const std::string toString() const;
    bool hasSameColorPieces(const Square* other) const;

    void setAction(ActionType type, ActionRelation relation, const Square* other);
    void dropAction(ActionType type, ActionRelation relation, const Square* other);
    void clearActions();
    void placePiece(const Piece& piece);
};
