#include <cassert>
#include <format>
#include <functional>
#include <iostream>
#include <string>

#include "../src/point/point.h"

#ifndef _CUSTOM_ASSERT_H_DECLS
#define _CUSTOM_ASSERT_H_DECLS
__BEGIN_DECLS

extern void __assert_strings_are_equal(
    const std::string& first,
    const std::string& second,
    const char *__file,
    unsigned int __line,
    const char *__function
);

extern void __assert_points_are_equal(
    const Point& first,
    const Point& second,
    const char *__file,
    unsigned int __line,
    const char *__function
);

extern void __assert_point_sets_are_equal(
    const PointSet& first,
    const PointSet& second,
    const char *__file,
    unsigned int __line,
    const char *__function
);

extern void __assert_error_was_thrown(
    std::function<void()> const& funct,
    const std::string& errorText,
    const char *__file,
    unsigned int __line,
    const char *__function
);

__END_DECLS
#endif

#define assert_strings_are_equal(first, second) ( \
    __assert_strings_are_equal(first, second, __ASSERT_FILE, __ASSERT_LINE, __ASSERT_FUNCTION) \
)

#define assert_points_are_equal(first, second) ( \
    __assert_points_are_equal(first, second, __ASSERT_FILE, __ASSERT_LINE, __ASSERT_FUNCTION) \
)

#define assert_point_sets_are_equal(first, second) ( \
    __assert_point_sets_are_equal(first, second, __ASSERT_FILE, __ASSERT_LINE, __ASSERT_FUNCTION) \
)

#define assert_error_was_thrown(funct, errorText) ( \
    __assert_error_was_thrown(funct, errorText, __ASSERT_FILE, __ASSERT_LINE, __ASSERT_FUNCTION) \
)
