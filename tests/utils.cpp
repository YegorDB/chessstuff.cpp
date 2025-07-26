#include "utils.h"

void __assert_points_are_equal(
    const Point& first,
    const Point& second,
    const char *__file,
    unsigned int __line,
    const char *__function
) {
    if (first != second) {
        std::string assertionMessage = std::format("Point{} == Point{}", first.toString(), second.toString());
        __assert_fail(&(assertionMessage[0]), __file, __line, __function);
    }
};

void __assert_point_sets_are_equal(
    const PointSet& first,
    const PointSet& second,
    const char *__file,
    unsigned int __line,
    const char *__function
) {
    if (first != second) {
        std::string assertionMessage = std::format("PointSet{} == PointSet{}", pointSetToString(first), pointSetToString(second));
        __assert_fail(&(assertionMessage[0]), __file, __line, __function);
    }
};
