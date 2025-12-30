#include "history.h"

const std::unordered_map<PieceType, std::string> HistoryMove::PIECE_TYPES_TO_SYMBOLS = {
    {PieceType::KING, "K"},
    {PieceType::QUEEN, "Q"},
    {PieceType::ROOK, "R"},
    {PieceType::BISHOP, "B"},
    {PieceType::KNIGHT, "N"},
    {PieceType::PAWN, ""},
};

HistoryMove::HistoryMove(
    PieceType pieceType,
    Point from,
    Point to,
    Type type,
    int checkersCount,
    bool isCheckMate,
    PieceType promotionType,
    PointSet otherCandidates
) : pieceType(pieceType), from(from), to(to), type(type), checkersCount(checkersCount), isCheckMate(isCheckMate), promotionType(promotionType), otherCandidates(otherCandidates) {
    _buidStringValue();
};

void HistoryMove::_buidStringValue() {
    if (type == Type::KING_SIDE_CASTLE) {
        _stringValue = "0-0";
    } else if (type == Type::QUEEN_SIDE_CASTLE) {
        _stringValue = "0-0-0";
    } else {
        _stringValue = PIECE_TYPES_TO_SYMBOLS.at(pieceType);

        if (!otherCandidates.empty() && pieceType != PieceType::PAWN) {
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
                _stringValue += s.getName();
            }
            if (hasSameRank) {
                _stringValue.push_back(s.getFile());
            }
            if (hasSameFile) {
                _stringValue.push_back(s.getRank());
            }
        }

        if (type == Type::TAKE) {
            if (pieceType == PieceType::PAWN) {
                _stringValue.push_back(Square{from}.getFile());
            }
            _stringValue.push_back('x');
        }

        _stringValue += Square{to}.getName();

        if (type == Type::PAWN_PROMOTION) {
            _stringValue.push_back('=');
            _stringValue += PIECE_TYPES_TO_SYMBOLS.at(promotionType);
        }
    }

    if (isCheckMate) {
        _stringValue.push_back('#');
    } else if (checkersCount > 0) {
        for (int i = 0; i < checkersCount; i++) {
            _stringValue.push_back('+');
        }
    }
}

const std::string HistoryMove::toString() const {
    return _stringValue;
};
