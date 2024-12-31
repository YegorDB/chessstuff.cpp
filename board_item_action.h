#include <unordered_set>

class BoardItemAction {
public:
    std::unordered_set<int> to;
    std::unordered_set<int> by;

    BoardItemAction();

    void clear();
    void insert_to(int hash);
    void insert_by(int hash);
};

class BoardItemActions {
public:
    BoardItemAction threat;
    BoardItemAction support;
    BoardItemAction place;
    BoardItemAction xray;

    BoardItemActions();

    void clear();
};
