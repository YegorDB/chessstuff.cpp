#include <cassert>
#include <format>
#include <iostream>

#include "../src/point/point.h"

#ifndef _CUSTOM_ASSERT_H_DECLS
#define _CUSTOM_ASSERT_H_DECLS
__BEGIN_DECLS

extern void __assert_points_are_equal(
    const Point& first,
    const Point& second,
    const char *__file,
    unsigned int __line,
    const char *__function
);

__END_DECLS
#endif

#define assert_points_are_equal(first, second) ( \
    __assert_points_are_equal(first, second, __ASSERT_FILE, __ASSERT_LINE, __ASSERT_FUNCTION) \
)
