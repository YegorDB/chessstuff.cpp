#include <unordered_map>
#include <unordered_set>

#include "square.h"

using ActionHashes = std::unordered_set<int>;

enum class ActionRelation {
    BY = 0,
    TO = 1
};

enum class ActionType {
    THREAT = 0,
    SUPPORT = 1,
    PLACE = 2,
    XRAY = 3
};

class Action {
private:
    std::unordered_map<ActionRelation, ActionHashes> _relations {
        {ActionRelation::BY, ActionHashes{}},
        {ActionRelation::TO, ActionHashes{}}
    };

public:
    Action();

    void insert(ActionRelation relation, Square square);
    void clear();
    const ActionHashes& get(ActionRelation relation) const;
};

class Actions {
private:
    std::unordered_map<ActionType, Action> _inners{
        {ActionType::THREAT, Action{}},
        {ActionType::SUPPORT, Action{}},
        {ActionType::PLACE, Action{}},
        {ActionType::XRAY, Action{}}
    };

public:
    Actions();

    void insert(ActionType type, ActionRelation relatio, Square square);
    void clear();
    const Action& get(ActionType type) const;
};
