#include "piece_pack.h"
#include "square.h"

struct BoardItem {
    Square square;
    PieceItem* piece = nullptr;
};

using BoardItems = std::vector<std::vector<BoardItem>>;

// main data is matrix 8x8
// each item contains:
// - square
// - piece on square (or null)
// - piece to peace interactions (attack, cover) direct and reverse [think about binds]
// - piece to square interactions (move, xray) direct and reverse
class Board {
private:
    BoardItems items;
    std::vector<PiecePack> piecePacks;

    void initItems();
    void initPiecePacks();
    void initOneSidePieces(bool isWhiteColor);
    void initPieces();

public:
    Board();

    const BoardItems& getItems() const;
};
