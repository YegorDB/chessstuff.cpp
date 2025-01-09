#pragma once

struct Direction {
    int dx;
    int dy;
    int maxDistance = 1;

    bool operator==(const Direction& other) const;
};
