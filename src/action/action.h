#pragma once

#include <unordered_map>

#include "../board/board.h"
#include "../point/point.h"

class Action {
public:
    enum class Relation {
        BY = 0,
        TO = 1
    };

    enum class Type {
        THREAT = 0,
        SUPPORT = 1,
        PLACE = 2,
        XRAY = 3,
        BIND = 4,
        AFTER_KING_RESTRICTION = 5
    };

    Action();

    void insert(Relation relation, const Point& point);
    void erase(Relation relation, const Point& point);
    void clear();
    const PointSet& get(Relation relation) const;

private:
    std::unordered_map<Relation, PointSet> _relations {
        {Relation::BY, PointSet{}},
        {Relation::TO, PointSet{}}
    };
};

class Actions {
private:
    std::unordered_map<Action::Type, Action> _inners{
        {Action::Type::THREAT, Action{}},
        {Action::Type::SUPPORT, Action{}},
        {Action::Type::PLACE, Action{}},
        {Action::Type::XRAY, Action{}},
        {Action::Type::BIND, Action{}},
        {Action::Type::AFTER_KING_RESTRICTION, Action{}}
    };

public:
    Actions();

    void operator=(const Actions& other);

    void insert(Action::Type type, Action::Relation relation, const Point& point);
    void erase(Action::Type type, Action::Relation relation, const Point& point);
    void clear();
    const Action& get(Action::Type type) const;
};

class ActionsPlaces {
public:
    using Items = std::unordered_map<Point, Actions, PointHasher>;

    ActionsPlaces();

    const Items& getItems() const;
    const Actions& getActions(const Point& point) const;
    void setAction(Action::Type type, const Point& byPoint, const Point& toPoint);
    void clearActions();
    void erasePoints(const Point& byPoint, Action::Type type, const PointSet& toPoints);
private:
    Items _items;
};
