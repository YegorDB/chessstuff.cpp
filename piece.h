#include <cstdint>
#include <string>
#include <vector>

struct Direction {
	uint16_t dx;
	uint16_t dy;
	uint16_t maxDistance = 1; 	
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
private:
	const std::vector<std::string> COLOR_NAMES = {"white", "black"};

	uint16_t color;
	std::string colorName;
	bool isFirstMove = true;
	// std::vector<Direction> moveDirections, attackDirections;

public:
	const PieceType type;
	const bool isWhiteColor;

	Piece(PieceType type, bool isWhiteColor);

	// addMoveDirection(Direction direction);
	// resetAdditionalDirections();
	// const std::vector<Direction>& getMoveDirections() const;
	// const std::vector<Direction>& attackDirections() const;
	const std::string& getColorName() const;
};
