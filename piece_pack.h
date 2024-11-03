#include "piece.h"

class PiecePack {
public:
    Piece king;
    std::vector<Piece> queens;
    std::vector<Piece> rooks;
    std::vector<Piece> bishops;
    std::vector<Piece> knights;
    std::vector<Piece> pawns;

    PiecePack(bool isWhiteColor);
};
