#include <unordered_map>
#include <unordered_set>

using BoardItemActionHashes = std::unordered_set<int>;

enum class BoardItemActionRelation {
    BY = 0,
    TO = 1
};

enum class BoardItemActionType {
    THREAT = 0,
    SUPPORT = 1,
    PLACE = 2,
    XRAY = 3
};

class BoardItemAction {
private:
    std::unordered_map<BoardItemActionRelation, BoardItemActionHashes> _relations {
        {BoardItemActionRelation::BY, BoardItemActionHashes{}},
        {BoardItemActionRelation::TO, BoardItemActionHashes{}}
    };

public:
    BoardItemAction();

    void insert(BoardItemActionRelation relation, int hash);
    void clear();
    const BoardItemActionHashes& get(BoardItemActionRelation relation) const;
};

class BoardItemActions {
private:
    std::unordered_map<BoardItemActionType, BoardItemAction> _inners{
        {BoardItemActionType::THREAT, BoardItemAction{}},
        {BoardItemActionType::SUPPORT, BoardItemAction{}},
        {BoardItemActionType::PLACE, BoardItemAction{}},
        {BoardItemActionType::XRAY, BoardItemAction{}}
    };

public:
    BoardItemActions();

    void insert(BoardItemActionType type, BoardItemActionRelation relation, int hash);
    void clear();
    const BoardItemAction& get(BoardItemActionType type) const;
};
