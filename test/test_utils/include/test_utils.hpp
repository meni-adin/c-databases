#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <array>
#include <string_view>

class TestUtils {
    static constexpr std::array<std::string_view, 3> MyArray = {
        "Value1",
        "Value2",
        "Value3"
    };

};

#endif // TEST_UTILS_H
