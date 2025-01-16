#include <unordered_set>

using BoardItemActionHashes = std::unordered_set<int>;

class BoardItemAction {
private:
    BoardItemActionHashes to;
    BoardItemActionHashes by;

public:
    BoardItemAction();

    void clear();
    void insertTo(int hash);
    void insertBy(int hash);
    const BoardItemActionHashes& getTo() const;
    const BoardItemActionHashes& getBy() const;
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
