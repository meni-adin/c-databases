#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string_view>
#include <vector>

class TestUtils {
public:
    const std::vector<const char *> &vecEmpty;
    const std::vector<const char *> &vecSingle;
    const std::vector<const char *> &vecZeroToNine;
    const std::vector<const char *> &vecZeroToNineOdd;
    const std::vector<const char *> &vecZeroToNineEven;

    TestUtils();

private:
    std::vector<const char *> vecEmpty_;
    std::vector<const char *> vecSingle_;
    std::vector<const char *> vecZeroToNine_;
    std::vector<const char *> vecZeroToNineOdd_;
    std::vector<const char *> vecZeroToNineEven_;

    void initVecEmpty();
    void initVecSingle();
    void initVecZeroToNine();
    void initVecZeroToNineOdd();
    void initVecZeroToNineEven();
};

#endif  // TEST_UTILS_H
