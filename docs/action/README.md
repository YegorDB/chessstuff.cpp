# Action


## Schema

```
Action
    Action <- ()
    insert <- Action::Relation
           <- Point
           -> void
    erase <- Action::Relation
          <- Point
          -> void
    clear -> void
    get <- Action::Relation
        -> PointSet

Actions
    Actions <- ()
    insert <- Action::Type
           <- Action::Relation
           <- Point
           -> void
    erase <- Action::Type
          <- Action::Relation
          <- Point
          -> void
    clear -> void
    get <- Action::Type
        -> Action

ActionsPlaces
    ActionsPlaces <- ()
    getItems -> std::unordered_map<Point, Actions, PointHasher>
    getActions <- Point
               -> Actions
    setAction <- Action::Type
    setAction <- Point
              -> void
    clearActions -> void
    erasePoints <- Point
                <- Action::Type
                <- PointSet
                -> void
```


## class Action

> Piece action related to points

### Methods

#### Action::insert(Action::Relation relation, const Point& point) -> void

> Insert point to relation

#### Action::erase(Action::Relation relation, const Point& point) -> void

> Erase point from relation

#### Action::clear() -> void

> Clear all relations points

#### Action::get(Action::Relation relation) -> const PointSet&

> Get relation points

### Constructors

#### Action::Action()

> Creates empty action

## enum class Action::Relation

> Action relation

### Values

- BY
- TO

## enum class Action::Type

> Action type

### Values

- THREAT
- SUPPORT
- PLACE
- XRAY
- BIND
- AFTER_KING_RESTRICTION


## class Actions

> Square actions

### Methods

#### Actions::insert(Action::Type type, Action::Relation relation, const Point& point) -> void

> Insert point to action relation

#### Actions::erase(Action::Type type, Action::Relation relation, const Point& point) -> void

> Erase point from action relation

#### Actions::clear() -> void

> Clear all actions relations points

#### Actions::get(Action::Type type) -> const Action&

> Get action

### Constructors

#### Actions::Actions()

> Creates empty actions


## class ActionsPlaces

> All squares actions

### Methods

#### ActionsPlaces::getItems() -> const std::unordered_map<Point, Actions, PointHasher>&

> Returns point actions map

#### ActionsPlaces::getActions(const Point& point) -> const Actions&

> Return square actions

#### ActionsPlaces::setAction(Action::Type type, const Point& byPoint, const Point& toPoint) -> void

> Set piece action by two points

#### ActionsPlaces::clearActions() -> void

> Clear all actions

#### ActionsPlaces::erasePoints(const Point& byPoint, Action::Type type, const PointSet& toPoints) -> void

> Erase destination points

### Constructors

#### ActionsPlaces::ActionsPlaces()

> Creates empty instance
