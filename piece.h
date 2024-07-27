#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

struct Direction {
    int dx;
    int dy;
    int maxDistance = 1;   
};

enum class PieceType {
    KING = 0,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN = 5
};

class Piece {
static const std::vector<std::string> COLOR_NAMES;

protected:
    std::vector<Direction> moveDirections;

public:
    const PieceType type;
    const bool isWhiteColor;

    Piece(PieceType type, bool isWhiteColor);

    const std::vector<Direction>& getMoveDirections() const;
    const std::vector<Direction>& getAttackDirections() const;
    const std::string& getColorName() const;
};

class King : public Piece {
public:
    King(bool isWhiteColor);
};

class Queen : public Piece {
public:
    Queen(bool isWhiteColor);
};

class Rook : public Piece {
public:
    Rook(bool isWhiteColor);
};

class Bishop : public Piece {
public:
    Bishop(bool isWhiteColor);
};

class Knight : public Piece {
public:
    Knight(bool isWhiteColor);
};

class Pawn : public Piece {
protected:
    std::vector<Direction> firstMoveDirections;
    std::vector<Direction> attackDirections;

public:
    Pawn(bool isWhiteColor);

    const std::vector<Direction>& getFirstMoveDirections() const;
    const std::vector<Direction>& getAttackDirections() const;
};
