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
static const std::unordered_map<PieceType, std::vector<Direction>> MOVE_DIRECTIONS;

private:
    int color;
    std::string colorName;
    bool isFirstMove = true;

public:
    const PieceType type;
    const bool isWhiteColor;

    Piece(PieceType type, bool isWhiteColor);

    const std::vector<Direction>* getMoveDirections() const;
    // const std::vector<Direction>& attackDirections() const;
    const std::string& getColorName() const;
};
