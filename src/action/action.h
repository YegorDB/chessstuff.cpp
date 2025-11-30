#pragma once

#include <unordered_map>

#include "../board/board.h"
#include "../point/point.h"

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

    void insert(ActionRelation relation, const Point& point);
    void erase(ActionRelation relation, const Point& point);
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

    void operator=(const Actions& other);

    void insert(ActionType type, ActionRelation relation, const Point& point);
    void erase(ActionType type, ActionRelation relation, const Point& point);
    void clear();
    const Action& get(ActionType type) const;
};

class ActionsPlaces {
public:
    using Items = std::unordered_map<Point, Actions, PointHasher>;

    ActionsPlaces();

    const Items& getItems() const;
    const Actions& getActions(const Point& point) const;
    void setAction(ActionType type, const Point& byPoint, const Point& toPoint);
    void clearActions();
    void erasePoints(const Point& byPoint, ActionType type, const PointSet& toPoints);
private:
    Items _items;
};
