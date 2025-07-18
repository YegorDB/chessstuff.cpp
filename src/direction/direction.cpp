#include "direction.h"

bool Direction::operator==(const Direction& other) const {
    return (
        this->dx == other.dx &&
        this->dy == other.dy &&
        this->maxDistance == other.maxDistance
    );
};
