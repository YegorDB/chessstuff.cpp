#include <unordered_set>

using BoardItemActionHashes = std::unordered_set<int>;

class BoardItemAction {
private:
    BoardItemActionHashes _to;
    BoardItemActionHashes _by;

public:
    BoardItemAction();

    void clear();
    void insertTo(int hash);
    void insertBy(int hash);
    const BoardItemActionHashes& getTo() const;
    const BoardItemActionHashes& getBy() const;
};

class BoardItemActions {
private:
    BoardItemAction _threat;
    BoardItemAction _support;
    BoardItemAction _place;
    BoardItemAction _xray;

public:
    BoardItemActions();

    void clear();

    BoardItemAction& getThreat();
    BoardItemAction& getSupport();
    BoardItemAction& getPlace();
    BoardItemAction& getXray();
};
