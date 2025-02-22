#include <unordered_map>
#include <unordered_set>

#include "point.h"

using ActionHashes = std::unordered_set<int>;

enum class ActionRelation {
    BY = 0,
    TO = 1
};

enum class ActionType {
    THREAT = 0,
    SUPPORT = 1,
    PLACE = 2,
    XRAY = 3,
    BIND = 4
};

class Action {
private:
    std::unordered_map<ActionRelation, ActionHashes> _relations {
        {ActionRelation::BY, ActionHashes{}},
        {ActionRelation::TO, ActionHashes{}}
    };

public:
    Action();

    void insert(ActionRelation relation, Point point);
    void clear();
    const ActionHashes& get(ActionRelation relation) const;
};

class Actions {
private:
    std::unordered_map<ActionType, Action> _inners{
        {ActionType::THREAT, Action{}},
        {ActionType::SUPPORT, Action{}},
        {ActionType::PLACE, Action{}},
        {ActionType::XRAY, Action{}},
        {ActionType::BIND, Action{}}
    };

public:
    Actions();

    void insert(ActionType type, ActionRelation relation, Point point);
    void clear();
    const Action& get(ActionType type) const;
};
