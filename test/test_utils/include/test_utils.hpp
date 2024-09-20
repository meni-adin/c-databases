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
    const std::vector<const char *> &vecZeroToNineWithDoubles;
    const char *const                doubleCommonPrefix;  // NOLINT (silent 'modernize-use-default-member-init')

    TestUtils();

private:
    std::vector<const char *> vecEmpty_;
    std::vector<const char *> vecSingle_;
    std::vector<const char *> vecZeroToNine_;
    std::vector<const char *> vecZeroToNineOdd_;
    std::vector<const char *> vecZeroToNineEven_;
    std::vector<const char *> vecZeroToNineWithDoubles_;

    void initVecEmpty();
    void initVecSingle();
    void initVecZeroToNine();
    void initVecZeroToNineOdd();
    void initVecZeroToNineEven();
    void initVecZeroToNineWithDoubles();
};

#endif  // TEST_UTILS_H
