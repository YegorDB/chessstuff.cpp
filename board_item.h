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

    void insertAction(BoardItemActionType type, BoardItem* other);

    static bool hasPiece(const BoardItem& item);
};

class BoardItems {
using Matrix = std::vector<std::vector<BoardItem>>;
using Filter = bool(const BoardItem&);

private:
    Matrix _matrix;

public:
    class Iterator {
    private:
        Matrix _matrix;
        int _index;
        Filter* _filter = nullptr;
        Point _point;
        void nextStep();
        void filterItems();
    public:
        Iterator(Matrix& matrix, int index);
        Iterator(Matrix& matrix, int index, Filter* filter);
        Iterator& operator++();
        BoardItem* operator*();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    class IteratorWithDitrection {
    private:
        Matrix _matrix;
        Point _point;
        Direction _direction;
        int _distance = 0;
        void nextStep();
    public:
        IteratorWithDitrection(Matrix& matrix, const Point& point, const Direction& direction, bool withStartPoint = false);
        IteratorWithDitrection& operator++();
        BoardItem* operator*();
        bool operator==(const IteratorWithDitrection& other) const;
        bool operator!=(const IteratorWithDitrection& other) const;
    };

    class Sequence {
    private:
        Iterator _begin, _end;
    public:
        Sequence(Iterator begin, Iterator end);
        Iterator begin() const;
        Iterator end() const;
    };

    class SequenceByDirection {
    private:
        IteratorWithDitrection _begin, _end;
    public:
        SequenceByDirection(IteratorWithDitrection begin, IteratorWithDitrection end);
        IteratorWithDitrection begin() const;
        IteratorWithDitrection end() const;
    };

    BoardItems();
    Sequence sequence();
    Sequence sequenceWithPieces();
    SequenceByDirection sequenceByDirection(const Point& point, const Direction& direction, bool withStartPoint = false);

    const BoardItem& getItem(const Point& point) const;
    void placePiece(Piece& piece, const Point& point);
};
