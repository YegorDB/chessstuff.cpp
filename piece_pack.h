#include "piece_item.h"

class PiecePack {
public:
    PieceItem king;
    std::vector<PieceItem> queens;
    std::vector<PieceItem> rooks;
    std::vector<PieceItem> bishops;
    std::vector<PieceItem> knights;
    std::vector<PieceItem> pawns;

    PiecePack(bool isWhiteColor);
};
