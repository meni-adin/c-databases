
#include "test_utils.hpp"

#include <cstddef>
#include <cstring>

#define DOUBLE_COMMON_PREFIX "Hello, world!"

TestUtils::TestUtils() :
    vecEmpty{vecEmpty_},
    vecSingle{vecSingle_},
    vecZeroToNine{vecZeroToNine_},
    vecZeroToNineOdd{vecZeroToNineOdd_},
    vecZeroToNineEven{vecZeroToNineEven_},
    vecZeroToNineWithDoubles{vecZeroToNineWithDoubles_},
    doubleCommonPrefix{DOUBLE_COMMON_PREFIX} {
    initVecEmpty();
    initVecSingle();
    initVecZeroToNine();
    initVecZeroToNineOdd();
    initVecZeroToNineEven();
    initVecZeroToNineWithDoubles();
}

void TestUtils::initVecEmpty() {
}

void TestUtils::initVecSingle() {
    TestUtils::vecSingle_.assign({
        "Hello, world!",
    });
}

void TestUtils::initVecZeroToNine() {
    TestUtils::vecZeroToNine_.assign({
        "0 Zero",
        "1 One",
        "2 Two",
        "3 Three",
        "4 Four",
        "5 Five",
        "6 Six",
        "7 Seven",
        "8 Eight",
        "9 Nine",
    });
}

void TestUtils::initVecZeroToNineOdd() {
    constexpr size_t stride = 2;

    for (auto it = vecZeroToNine.cbegin() + 1; it < vecZeroToNine.cend(); it += stride) {
        vecZeroToNineOdd_.push_back(*it);
        if (static_cast<size_t>(vecZeroToNine.cend() - it) < stride) {
            break;
        }
    }
}

void TestUtils::initVecZeroToNineEven() {
    constexpr size_t stride = 2;

    for (auto it = vecZeroToNine.cbegin(); it < vecZeroToNine.cend(); it += stride) {
        vecZeroToNineEven_.push_back(*it);
        if (static_cast<size_t>(vecZeroToNine.cend() - it) < stride) {
            break;
        }
    }
}

void TestUtils::initVecZeroToNineWithDoubles() {
    static constexpr size_t FIRST_ELEMENT_INDEX  = 0;
    static constexpr size_t MIDDLE_ELEMENT_INDEX = 5;
    static constexpr size_t LAST_ELEMENT_INDEX   = 9;

    for (const auto *const iter : vecZeroToNine) {
        if (strcmp(iter, vecZeroToNine[FIRST_ELEMENT_INDEX]) == 0) {
            vecZeroToNineWithDoubles_.push_back(DOUBLE_COMMON_PREFIX " 0");
        }
        if (strcmp(iter, vecZeroToNine[MIDDLE_ELEMENT_INDEX]) == 0) {
            vecZeroToNineWithDoubles_.push_back(DOUBLE_COMMON_PREFIX " 1");
            vecZeroToNineWithDoubles_.push_back(DOUBLE_COMMON_PREFIX " 2");
        }
        vecZeroToNineWithDoubles_.push_back(iter);
        if (strcmp(iter, vecZeroToNine[LAST_ELEMENT_INDEX]) == 0) {
            vecZeroToNineWithDoubles_.push_back(DOUBLE_COMMON_PREFIX " 3");
        }
    }
}
