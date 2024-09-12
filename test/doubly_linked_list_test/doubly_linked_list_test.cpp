#include <gtest/gtest.h>
#include <memory>
#include <ranges>
#include <vector>

#include "doubly_linked_list.h"
#include "errors.h"
#include "test_utils.hpp"

using namespace std;
using namespace testing;

#define XSTR(var) #var
#define STR(var)  XSTR(var)

class DoublyLinkedListTest : public ::testing::Test {
protected:
    static inline unique_ptr<TestUtils> testUtils;

    static void SetUpTestSuite() {
        testUtils = make_unique<TestUtils>();
    }

    static void TearDownTestSuite() {
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

#ifdef C_DATABASES_SAFE_MODE
TEST_F(DoublyLinkedListTest, InvalidArguments) {
    ASSERT_EQ(DoublyLinkedList_newList(nullptr), ERR_BAD_ARGUMENT);
}
#endif  // C_DATABASES_SAFE_MODE

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
        ASSERT_EQ(DoublyLinkedList_insertNode(list, nullptr, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)element),
                  SUCCESS);
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
