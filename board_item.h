#include "board_item_action.h"
#include "piece_pack.h"
#include "square.h"

class BoardItem {
public:
    Square square;
    Piece* piece = nullptr;
    BoardItemActions actions;

    BoardItem(Square square);
    BoardItem(Square square, Piece* piece);

    static bool hasPiece(const BoardItem& item);
};

class BoardItems {
using Matrix = std::vector<std::vector<BoardItem>>;
using Filter = bool(const BoardItem&);

// private:
//     Matrix _matrix;

public:
    class Iterator {
    private:
        Matrix _matrix;
        int _index;
        Filter* _filter = nullptr;
        Point _point;
    public:
        Iterator(Matrix& matrix, int index);
        Iterator(Matrix& matrix, int index, Filter* filter);
        Iterator& operator++();
        BoardItem* operator*();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    class Sequence {
    private:
        Iterator _begin, _end;
    public:
        Sequence(Iterator begin, Iterator end);
        Iterator begin() const;
        Iterator end() const;
    };

    Matrix matrix;

    BoardItems();
    Sequence sequence();
    Sequence sequenceWithPieces();
    // const Matrix& matrix() const;

    void placePiece(Piece& piece, const Point& point);
};
