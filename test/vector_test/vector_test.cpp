#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <ranges>
#include <vector>

#include "errors.h"
#include "test_utils.hpp"
#include "vector.h"

using namespace std;
using namespace testing;

class DestructorMock {
public:
    MOCK_METHOD(void, destructor, (void *));
};

class VectorTest : public ::testing::Test {
public:
    static inline unique_ptr<DestructorMock> destructorMock;

protected:
    static inline unique_ptr<TestUtils> testUtils;

    static void SetUpTestSuite() {
        testUtils = make_unique<TestUtils>();
    }

    static void TearDownTestSuite() {
    }

    void SetUp() override {
        destructorMock = make_unique<DestructorMock>();
    }

    void TearDown() override {
        destructorMock.reset();
    }

    static void verifyVectorContent(const Vector_t *vector, const std::vector<const char *> &elements) {
        status_t status;
        size_t   length;
        void    *data;

        ASSERT_EQ(Vector_getLength(vector, &length), SUCCESS);
        ASSERT_EQ(length, elements.size());
        for (const size_t index : std::ranges::iota_view(size_t(0), length)) {
            ASSERT_EQ(Vector_getElement(vector, index, &data), SUCCESS);
            EXPECT_STREQ(elements[index], (const char *)data);
        }
    }
};

extern "C" {
void destructor_callback(void *data) {
    VectorTest::destructorMock->destructor(data);
}
}

TEST_F(VectorTest, NewAndDelete) {
    Vector_t   *vector;
    const auto &elements = testUtils->vecEmpty;

    ASSERT_EQ(Vector_newVector(&vector), SUCCESS);
    verifyVectorContent(vector, elements);
    ASSERT_EQ(Vector_deleteVector(vector, nullptr), SUCCESS);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
