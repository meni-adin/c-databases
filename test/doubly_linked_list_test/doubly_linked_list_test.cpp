
#include <gmock/gmock.h>
#include "doubly_linked_list.h"

using namespace std;
using namespace testing;

class DoublyLinkedListTest : public ::testing::Test
{
protected:
    void test_DoublyLinkedList_new(DoublyLinkedList_t **list, status_t expectedStatus=SUCCESS)
    {
        status_t status;

        status = DoublyLinkedList_newList(list);
        EXPECT_EQ(status, expectedStatus);
    }

    void test_DoublyLinkedList_delete(DoublyLinkedList_t *list)
    {
        status_t status;

        status = DoublyLinkedList_deleteList(list);
        EXPECT_EQ(status, SUCCESS);
    }
};


#ifdef C_DATABASES_SAFE_MODE
TEST_F(DoublyLinkedListTest, InvalidArguments)
{
    test_DoublyLinkedList_new(NULL, ERR_BAD_ARGUMENT);
}
#endif // C_DATABASES_SAFE_MODE

TEST_F(DoublyLinkedListTest, InitAndDeinit)
{
    DoublyLinkedList_t *list;

    test_DoublyLinkedList_new(&list);
    test_DoublyLinkedList_delete(list);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
