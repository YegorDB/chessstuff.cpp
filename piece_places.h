#include <unordered_map>

#include "piece.h"
#include "point.h"

using PiecePlaces = std::unordered_map<Point, PieceInfo, PointHasher>;
