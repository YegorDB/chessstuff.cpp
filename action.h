#pragma once

#include <unordered_map>

#include "point.h"

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
    std::unordered_map<ActionRelation, PointSet> _relations {
        {ActionRelation::BY, PointSet{}},
        {ActionRelation::TO, PointSet{}}
    };

public:
    Action();

    void insert(ActionRelation relation, Point point);
    void clear();
    const PointSet& get(ActionRelation relation) const;
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
