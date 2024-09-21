#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "doubly_linked_list.h"
#include "errors.h"
#include "test_utils.hpp"

using namespace std;
using namespace testing;

class DestructorMock {
public:
    MOCK_METHOD(void, destructor, (void *));
};

class DoublyLinkedListTest : public ::testing::Test {
public:
    static inline unique_ptr<DestructorMock> destructorMock;
    static const DoublyLinkedListDirection_t directionTooSmall{(DoublyLinkedListDirection_t)-1};
    static const DoublyLinkedListDirection_t directionTooLarge{(DoublyLinkedListDirection_t)2};

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

    static void verifyListContent(const DoublyLinkedList_t *list, const vector<const char *> &elements) {
        status_t                status;
        DoublyLinkedListNode_t *node;
        void                   *data;

        ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);
        for (const auto *element : elements) {
            ASSERT_EQ(DoublyLinkedList_getData(node, &data), SUCCESS);
            EXPECT_STREQ(element, (const char *)data);
            ASSERT_EQ(DoublyLinkedList_getNext(list, &node), SUCCESS);
        }
        EXPECT_EQ(node, nullptr);

        ASSERT_EQ(DoublyLinkedList_getTail(list, &node), SUCCESS);
        for (const auto *element : std::ranges::reverse_view(elements)) {
            ASSERT_EQ(DoublyLinkedList_getData(node, &data), SUCCESS);
            EXPECT_STREQ(element, (const char *)data);
            ASSERT_EQ(DoublyLinkedList_getPrev(list, &node), SUCCESS);
        }
        EXPECT_EQ(node, nullptr);
    }
};

extern "C" {
int c_str_comparator(const void *data1, const void *data2) {
    return strcmp((const char *)data1, (const char *)data2);
}

int c_str_prefix_comparator(const void *data1, const void *data2) {
    const char *data1Ptr = (const char *)data1;
    const char *data2Ptr = (const char *)data2;
    for (; (*data1Ptr != '\0') && (*data2Ptr != '\0'); ++data1Ptr, ++data2Ptr) {
        if (*data1Ptr != *data2Ptr) {
            return 1;
        }
    }
    return 0;
}

void destructor_callback(void *data) {
    DoublyLinkedListTest::destructorMock->destructor(data);
}
}

TEST_F(DoublyLinkedListTest, NewAndDelete) {
    DoublyLinkedList_t *list;
    const auto         &elements = testUtils->vecEmpty;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertSingleElementAtHead) {
    DoublyLinkedList_t *list;
    const auto         &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertSingleElementAtTail) {
    DoublyLinkedList_t *list;
    const auto         &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAtHead) {
    DoublyLinkedList_t *list;
    const auto         &elements = testUtils->vecZeroToNine;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *element : std::ranges::reverse_view(elements)) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)element), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAtTail) {
    DoublyLinkedList_t *list;
    const auto         &elements = testUtils->vecZeroToNine;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsBeforeReference) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    const auto             &elements = testUtils->vecZeroToNine;
    auto                    iter     = elements.crbegin();

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)*iter), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);
    for (++iter; iter != elements.crend(); ++iter) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)*iter), SUCCESS);
        ASSERT_EQ(DoublyLinkedList_getPrev(list, &node), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAfterReference) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    const auto             &elements = testUtils->vecZeroToNine;
    auto                    iter     = elements.cbegin();

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)*iter), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);
    for (++iter; iter != elements.cend(); ++iter) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)*iter), SUCCESS);
        ASSERT_EQ(DoublyLinkedList_getNext(list, &node), SUCCESS);
    }
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, RemoveEvenElements) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    const auto             &elements     = testUtils->vecZeroToNine;
    const auto             &oddElements  = testUtils->vecZeroToNineOdd;
    const auto             &evenElements = testUtils->vecZeroToNineEven;

    for (const auto *const iter : evenElements) {
        EXPECT_CALL(*destructorMock, destructor((void *)iter));
    }

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);
    for (const auto *const iter : oddElements) {
        node = nullptr;
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (void *)iter), SUCCESS);
        ASSERT_EQ(DoublyLinkedList_removeNode(list, node), SUCCESS);
    }
    verifyListContent(list, evenElements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, destructor_callback), SUCCESS);
}

TEST_F(DoublyLinkedListTest, RemoveOddElements) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    const auto             &elements     = testUtils->vecZeroToNine;
    const auto             &oddElements  = testUtils->vecZeroToNineOdd;
    const auto             &evenElements = testUtils->vecZeroToNineEven;

    for (const auto *const iter : oddElements) {
        EXPECT_CALL(*destructorMock, destructor((void *)iter));
    }

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);
    for (const auto *const iter : evenElements) {
        node = nullptr;
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (void *)iter), SUCCESS);
        ASSERT_EQ(DoublyLinkedList_removeNode(list, node), SUCCESS);
    }
    verifyListContent(list, oddElements);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, destructor_callback), SUCCESS);
}

TEST_F(DoublyLinkedListTest, FindInEmptyList) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node = nullptr;
    void                   *data;
    const auto             &elements = testUtils->vecEmpty;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    verifyListContent(list, elements);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, FindInListNotContaining) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node = nullptr;
    void                   *data;
    const auto             &elements = testUtils->vecZeroToNine;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);

    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_getTail(list, &node), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_getTail(list, &node), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, FindAllDoublesFromHead) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node = nullptr;
    void                   *data;
    const auto             &elements = testUtils->vecZeroToNineWithDoubles;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);

    for (const size_t index : std::ranges::iota_view(size_t(0), size_t(4))) {
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_prefix_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
        ASSERT_NE(node, nullptr);
        ASSERT_EQ(DoublyLinkedList_getData(node, &data), SUCCESS);
        auto currentDoubleWithIndex = (string(testUtils->doubleCommonPrefix) += " ") += to_string(index);
        ASSERT_STREQ((const char *)data, currentDoubleWithIndex.c_str());
    }
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_prefix_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, FindAllDoublesFromTail) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node = nullptr;
    void                   *data;
    const auto             &elements = testUtils->vecZeroToNineWithDoubles;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list, elements);

    for (const size_t index : std::ranges::iota_view(size_t(0), size_t(4)) | std::views::reverse) {
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_prefix_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
        ASSERT_NE(node, nullptr);
        ASSERT_EQ(DoublyLinkedList_getData(node, &data), SUCCESS);
        auto currentDoubleWithIndex = (string(testUtils->doubleCommonPrefix) += " ") += to_string(index);
        ASSERT_STREQ((const char *)data, currentDoubleWithIndex.c_str());
    }
    ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, c_str_prefix_comparator, (const void *)testUtils->doubleCommonPrefix), SUCCESS);
    ASSERT_EQ(node, nullptr);

    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

#ifdef C_DATABASES_SAFE_MODE

TEST_F(DoublyLinkedListTest, InvalidArguments) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node = nullptr;
    void                   *data;
    const auto             &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);

    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(nullptr, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, directionTooSmall, (void *)iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, directionTooLarge, (void *)iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }

    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_findData(nullptr, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_findData(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, directionTooSmall, c_str_comparator, iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, directionTooLarge, c_str_comparator, iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, nullptr, iter), ERR_BAD_ARGUMENT);
        ASSERT_EQ(DoublyLinkedList_findData(list, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, iter), SUCCESS);
    }

    ASSERT_EQ(DoublyLinkedList_getData(nullptr, &data), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getData(node, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getData(node, &data), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_getHead(nullptr, &node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getHead(list, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getHead(list, &node), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_getNext(nullptr, &node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getNext(list, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getNext(list, &node), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_getTail(nullptr, &node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getTail(list, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getTail(list, &node), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_getPrev(nullptr, &node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getPrev(list, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getPrev(list, &node), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_deleteList(nullptr, nullptr), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_deleteList(list, nullptr), SUCCESS);
}

TEST_F(DoublyLinkedListTest, NodeFromOtherList) {
    DoublyLinkedList_t     *list1;
    DoublyLinkedList_t     *list2;
    DoublyLinkedListNode_t *node     = nullptr;
    const auto             &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(&list1), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_newList(&list2), SUCCESS);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_insertNode(list1, nullptr, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter), SUCCESS);
    }
    verifyListContent(list1, elements);
    ASSERT_EQ(DoublyLinkedList_getTail(list1, &node), SUCCESS);

    ASSERT_EQ(DoublyLinkedList_removeNode(list2, node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getNext(list2, &node), ERR_BAD_ARGUMENT);
    ASSERT_EQ(DoublyLinkedList_getPrev(list2, &node), ERR_BAD_ARGUMENT);
    for (const auto *const iter : elements) {
        ASSERT_EQ(DoublyLinkedList_findData(list2, &node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, c_str_comparator, iter), ERR_BAD_ARGUMENT);
    }

    ASSERT_EQ(DoublyLinkedList_deleteList(list1, nullptr), SUCCESS);
    ASSERT_EQ(DoublyLinkedList_deleteList(list2, nullptr), SUCCESS);
}

#endif  // C_DATABASES_SAFE_MODE

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
