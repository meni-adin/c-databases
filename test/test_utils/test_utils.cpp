
#include "test_utils.hpp"

TestUtils::TestUtils() :
        vecEmpty         {vecEmpty_},
        vecSingle        {vecSingle_},
        vecZeroToNine    {vecZeroToNine_},
        vecZeroToNineOdd {vecZeroToNineOdd_},
        vecZeroToNineEven{vecZeroToNineEven_}
    {
        initVecEmpty();
        initVecSingle();
        initVecZeroToNine();
        initVecZeroToNineOdd();
        initVecZeroToNineEven();
    };

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
    for (auto it = vecZeroToNine.cbegin() + 1; it < vecZeroToNine.cend(); it += 2)
        vecZeroToNineOdd_.push_back(*it);
}

void TestUtils::initVecZeroToNineEven() {
    for (auto it = vecZeroToNine.cbegin(); it < vecZeroToNine.cend(); it += 2)
        vecZeroToNineEven_.push_back(*it);
}
