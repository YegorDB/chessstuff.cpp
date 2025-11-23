#include "utils.h"

void __assert_strings_are_equal(
    const std::string& first,
    const std::string& second,
    const char *__file,
    unsigned int __line,
    const char *__function
) {
    if (first != second) {
        std::string assertionMessage = std::format("{} == {}", first, second);
        __assert_fail(&(assertionMessage[0]), __file, __line, __function);
    }
};

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

void __assert_error_was_thrown(
    std::function<void()> const& funct,
    const std::string& errorText,
    const char *__file,
    unsigned int __line,
    const char *__function
) {
    try {
        funct();
    } catch(const std::runtime_error& e) {
        __assert_strings_are_equal(e.what(), errorText, __file, __line, __function);
        return;
    }
    std::string assertionMessage = std::format("Error ({}) was thrown", errorText);
    __assert_fail(&(assertionMessage[0]), __file, __line, __function);
};
