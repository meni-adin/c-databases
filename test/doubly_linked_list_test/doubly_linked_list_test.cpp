
#include <gtest/gtest.h>
#include <memory>

#include "doubly_linked_list.h"
#include "test_utils.hpp"

using namespace std;
using namespace testing;

class DoublyLinkedListTest : public ::testing::Test {
protected:
    static inline unique_ptr<TestUtils> testUtils;

    static void SetUpTestSuite() {
        testUtils = make_unique<TestUtils>();
    }

    static void TearDownTestSuite() {
    }

    void test_DoublyLinkedList_deleteList(DoublyLinkedList_t              *list,
                                          DoublyLinkedListDataDestructor_t destructor     = NULL,
                                          status_t                         expectedStatus = SUCCESS) {
        status_t status;

        status = DoublyLinkedList_deleteList(list, destructor);
        EXPECT_EQ(status, expectedStatus);
    }

    void test_DoublyLinkedList_insertNode(DoublyLinkedList_t           *list,
                                          const DoublyLinkedListNode_t *reference,
                                          DoublyLinkedListDirection_t   direction,
                                          void                         *data) {
        status_t status;

        status = DoublyLinkedList_insertNode(list, reference, direction, data);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_removeNode(DoublyLinkedList_t *list, DoublyLinkedListNode_t *node) {
        status_t status;

        status = DoublyLinkedList_removeNode(list, node);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_getHead(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
        status_t status;

        status = DoublyLinkedList_getHead(list, node);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_getTail(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
        status_t status;

        status = DoublyLinkedList_getTail(list, node);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_getNext(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
        status_t status;

        status = DoublyLinkedList_getNext(list, node);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_getPrev(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
        status_t status;

        status = DoublyLinkedList_getPrev(list, node);
        EXPECT_EQ(status, SUCCESS);
    }

    void test_DoublyLinkedList_getData(const DoublyLinkedListNode_t *node, void **data) {
        status_t status;

        status = DoublyLinkedList_getData(node, data);
        EXPECT_EQ(status, SUCCESS);
    }

    void verifyListContent(const DoublyLinkedList_t *list, const vector<const char *> &elements) {
        status_t                status;
        DoublyLinkedListNode_t *node;
        void                   *data;

        test_DoublyLinkedList_getHead(list, &node);
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter) {
            test_DoublyLinkedList_getData(node, &data);
            EXPECT_STREQ(*iter, (const char *)data);
            test_DoublyLinkedList_getNext(list, &node);
        }
        EXPECT_EQ(node, nullptr);

        test_DoublyLinkedList_getTail(list, &node);
        for (auto iter = elements.crbegin(); iter != elements.crend(); ++iter) {
            test_DoublyLinkedList_getData(node, &data);
            EXPECT_STREQ(*iter, (const char *)data);
            test_DoublyLinkedList_getPrev(list, &node);
        }
        EXPECT_EQ(node, nullptr);
    }
};

#ifdef C_DATABASES_SAFE_MODE
TEST_F(DoublyLinkedListTest, InvalidArguments) {
    ASSERT_EQ(DoublyLinkedList_newList(NULL), ERR_BAD_ARGUMENT);
}
#endif  // C_DATABASES_SAFE_MODE

TEST_F(DoublyLinkedListTest, NewAndDelete) {
    DoublyLinkedList_t *list;
    auto               &elements = testUtils->vecEmpty;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertSingleElementAtHead) {
    DoublyLinkedList_t *list;
    auto               &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto iter : elements) {
        test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)iter);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertSingleElementAtTail) {
    DoublyLinkedList_t *list;
    auto               &elements = testUtils->vecSingle;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto iter : elements) {
        test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAtHead) {
    DoublyLinkedList_t *list;
    auto               &elements = testUtils->vecZeroToNine;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (auto iter = elements.crbegin(); iter != elements.crend(); ++iter) {
        test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)*iter);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAtTail) {
    DoublyLinkedList_t *list;
    auto               &elements = testUtils->vecZeroToNine;

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    for (const auto iter : elements) {
        test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)iter);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsBeforeReference) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    auto                   &elements = testUtils->vecZeroToNine;
    auto                    iter     = elements.crbegin();

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)*iter);
    test_DoublyLinkedList_getHead(list, &node);
    for (++iter; iter != elements.crend(); ++iter) {
        test_DoublyLinkedList_insertNode(list, node, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)*iter);
        test_DoublyLinkedList_getPrev(list, &node);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

TEST_F(DoublyLinkedListTest, InsertMultipleElementsAfterReference) {
    DoublyLinkedList_t     *list;
    DoublyLinkedListNode_t *node;
    auto                   &elements = testUtils->vecZeroToNine;
    auto                    iter     = elements.cbegin();

    ASSERT_EQ(DoublyLinkedList_newList(&list), SUCCESS);
    test_DoublyLinkedList_insertNode(list, NULL, DOUBLY_LINKED_LIST_DIRECTION_HEAD, (void *)*iter);
    test_DoublyLinkedList_getHead(list, &node);
    for (++iter; iter != elements.cend(); ++iter) {
        test_DoublyLinkedList_insertNode(list, node, DOUBLY_LINKED_LIST_DIRECTION_TAIL, (void *)*iter);
        test_DoublyLinkedList_getNext(list, &node);
    }
    verifyListContent(list, elements);
    test_DoublyLinkedList_deleteList(list);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
