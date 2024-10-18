#include "piece_item.h"

PieceItem::PieceItem(King king) : value(PieceValue{king}), type(PieceType::KING) {};

PieceItem::PieceItem(Queen queen) : value(PieceValue{queen}), type(PieceType::QUEEN) {};

PieceItem::PieceItem(Rook rook) : value(PieceValue{rook}), type(PieceType::ROOK) {};

PieceItem::PieceItem(Bishop bishop) : value(PieceValue{bishop}), type(PieceType::BISHOP) {};

PieceItem::PieceItem(Knight knight) : value(PieceValue{knight}), type(PieceType::KNIGHT) {};

PieceItem::PieceItem(Pawn pawn) : value(PieceValue{pawn}), type(PieceType::PAWN) {};

King PieceItem::getKing() {
    return std::get<King>(value);
};

Queen PieceItem::getQueen() {
    return std::get<Queen>(value);
};

Rook PieceItem::getRook() {
    return std::get<Rook>(value);
};

Bishop PieceItem::getBishop() {
    return std::get<Bishop>(value);
};

Knight PieceItem::getKnight() {
    return std::get<Knight>(value);
};

Pawn PieceItem::getPawn() {
    return std::get<Pawn>(value);
};
