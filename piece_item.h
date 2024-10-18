#include "piece.h"
#include <variant>

using PieceValue = std::variant<King, Queen, Rook, Bishop, Knight, Pawn>;

class PieceItem {
public:
    PieceValue value;
    PieceType type;

    PieceItem(King king);
    PieceItem(Queen queen);
    PieceItem(Rook rook);
    PieceItem(Bishop bishop);
    PieceItem(Knight knight);
    PieceItem(Pawn pawn);

    King getKing();
    Queen getQueen();
    Rook getRook();
    Bishop getBishop();
    Knight getKnight();
    Pawn getPawn();
};
