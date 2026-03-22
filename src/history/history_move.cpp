#include "history.h"

const std::unordered_map<Piece::Type, std::string> HistoryMove::PIECE_TYPES_TO_SYMBOLS = {
    {Piece::Type::KING, "K"},
    {Piece::Type::QUEEN, "Q"},
    {Piece::Type::ROOK, "R"},
    {Piece::Type::BISHOP, "B"},
    {Piece::Type::KNIGHT, "N"},
    {Piece::Type::PAWN, ""},
};

HistoryMove::HistoryMove() {};

HistoryMove::HistoryMove(
    Piece::Type pieceType,
    Point from,
    Point to,
    Type type,
    int checkersCount,
    bool isCheckMate,
    Piece::Type promotionType,
    PointSet otherCandidates
) : pieceType(pieceType), from(from), to(to), type(type), checkersCount(checkersCount), isCheckMate(isCheckMate), promotionType(promotionType), otherCandidates(otherCandidates) {};

void HistoryMove::operator=(const HistoryMove& other) {
    pieceType = other.pieceType;
    from = other.from;
    to = other.to;
    type = other.type;
    checkersCount = other.checkersCount;
    isCheckMate = other.isCheckMate;
    promotionType = other.promotionType;
    otherCandidates = other.otherCandidates;
};

std::string HistoryMove::toString() const {
    std::string stringValue;

    if (type == Type::KING_SIDE_CASTLE) {
        stringValue = "0-0";
    } else if (type == Type::QUEEN_SIDE_CASTLE) {
        stringValue = "0-0-0";
    } else {
        stringValue = PIECE_TYPES_TO_SYMBOLS.at(pieceType);

        if (!otherCandidates.empty() && pieceType != Piece::Type::PAWN) {
            bool hasSameFile = false;
            bool hasSameRank = false;
            for (Point p : otherCandidates) {
                if (from.x() == p.x()) {
                    hasSameFile = true;
                }
                if (from.y() == p.y()) {
                    hasSameRank = true;
                }
            }

            Square s{from};
            if (!hasSameFile && !hasSameRank) {
                stringValue += s.getName();
            }
            if (hasSameRank) {
                stringValue.push_back(s.getFile());
            }
            if (hasSameFile) {
                stringValue.push_back(s.getRank());
            }
        }

        if (type == Type::TAKE) {
            if (pieceType == Piece::Type::PAWN) {
                stringValue.push_back(Square{from}.getFile());
            }
            stringValue.push_back('x');
        }

        stringValue += Square{to}.getName();

        if (type == Type::PAWN_PROMOTION) {
            stringValue.push_back('=');
            stringValue += PIECE_TYPES_TO_SYMBOLS.at(promotionType);
        }
    }

    if (isCheckMate) {
        stringValue.push_back('#');
    } else if (checkersCount > 0) {
        for (int i = 0; i < checkersCount; i++) {
            stringValue.push_back('+');
        }
    }

    return stringValue;
};
