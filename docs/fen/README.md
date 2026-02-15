# FEN


##  Schema

```
FEN
    FEN <- std::string
    FEN <- State
    INITIAL_POSITION -> std::string
    getRawString -> std::string
    getRawStringParts -> std::vector<std::string>
    getState -> State
```


## class FEN

> Transform FEN strings to State and vice versa

### Properties

#### static const std::string INITIAL_POSITION

> Classical chess initial position FEN string

### Methods

#### FEN::getRawString() -> const std::string&

> Returns FEN string

#### FEN::getRawStringParts() -> const std::vector<std::string>&

> Returns FEN string parts

#### FEN::getState() -> const State&

> Returns State

### Constructors

#### FEN::FEN(const std::string& rawString)

> Creates instance by FEN string

#### FEN::FEN(const State& state)

> Creates instance by state
