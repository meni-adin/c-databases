
#include <stdlib.h>
#include <assert.h>
#include "config.h"
#include "doubly_linked_list.h"
#include "errors.h"

typedef struct DoublyLinkedListNode_t_ DoublyLinkedListNode_t;

struct DoublyLinkedListNode_t_
{
    DoublyLinkedListNode_t *prev;
    DoublyLinkedListNode_t *next;
    void                   *data;
#ifdef C_DATABASES_SAFE_MODE
    DoublyLinkedList_t     *list;
#endif // C_DATABASES_SAFE_MODE
};

struct DoublyLinkedList_t_
{
    DoublyLinkedListNode_t *head;
};

#define DOUBLY_LINKED_LIST_DIRECTION_IS_VALID(direction) ((direction == DOUBLY_LINKED_LIST_DIRECTION_HEAD) || (direction == DOUBLY_LINKED_LIST_DIRECTION_TAIL))

static inline void DoublyLinkedList_insertNodeBefore(DoublyLinkedListNode_t *reference, DoublyLinkedListNode_t *newNode)
{
    newNode->prev = reference->prev;
    newNode->next = reference;
    newNode->prev->next = newNode->next->prev = newNode;
}

status_t DoublyLinkedList_newList(DoublyLinkedList_t **list)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list)
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    DoublyLinkedList_t *newList = malloc(sizeof(*newList));

    if(!newList)
    {
        return ERR_MEM_ALLOC;
    }

    *newList = (DoublyLinkedList_t) {
        .head = NULL,
    };

    *list = newList;

    return SUCCESS;
}

status_t DoublyLinkedList_deleteList(DoublyLinkedList_t *list, DoublyLinkedListDataDestructor_t destructor)
{
    DoublyLinkedListNode_t *currentNode, *nextNode;
#ifdef C_DATABASES_SAFE_MODE
    if (!list)
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    if (list->head)
    {
        list->head->prev->next = NULL;
        for (currentNode = list->head, nextNode = currentNode->next; currentNode != NULL; currentNode = nextNode)
        {
            nextNode = currentNode->next;
            destructor ? destructor(currentNode->data) : (void) destructor;
    #ifdef C_DATABASES_SAFE_MODE
            *currentNode = (DoublyLinkedListNode_t) {0};
    #endif // C_DATABASES_SAFE_MODE
            free(currentNode);
        }
    }

#ifdef C_DATABASES_SAFE_MODE
    *list = (DoublyLinkedList_t) {0};
#endif // C_DATABASES_SAFE_MODE
    free(list);

    return SUCCESS;
}

status_t DoublyLinkedList_insertNode(DoublyLinkedList_t *list, const DoublyLinkedListNode_t *reference, DoublyLinkedListDirection_t direction, void *data)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !DOUBLY_LINKED_LIST_DIRECTION_IS_VALID(direction))
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    DoublyLinkedListNode_t *newNode = malloc(sizeof(*newNode));

    if(!newNode)
        return ERR_MEM_ALLOC;

    newNode->data = data;
#ifdef C_DATABASES_SAFE_MODE
    newNode->list = list;
#endif // C_DATABASES_SAFE_MODE

    if (!list->head)
    {
        newNode->prev = newNode->next = newNode;
        list->head = newNode;
    }
    else
    {
        if (!reference)
        {
            DoublyLinkedList_insertNodeBefore(list->head, newNode);
            if (direction == DOUBLY_LINKED_LIST_DIRECTION_HEAD)
                list->head = newNode;
        }
        else
        {
            if (direction == DOUBLY_LINKED_LIST_DIRECTION_HEAD)
            {
                DoublyLinkedList_insertNodeBefore((DoublyLinkedListNode_t *)reference, newNode);
                if (reference == list->head)
                    list->head = newNode;
            }
            else
                DoublyLinkedList_insertNodeBefore(reference->next, newNode);
        }
    }

    return SUCCESS;
}

status_t DoublyLinkedList_removeNode(DoublyLinkedList_t *list, DoublyLinkedListNode_t *node)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || (node->list != list))
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    if (list->head == node)
        list->head = node->next;

    node->next = node->prev;
    node->prev = node->next;
#ifdef C_DATABASES_SAFE_MODE
    *node = (DoublyLinkedListNode_t) {0};
#endif // C_DATABASES_SAFE_MODE
    free(node);

    return SUCCESS;
}

status_t DoublyLinkedList_getHead(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node)
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    *node = list->head;

    return SUCCESS;
}

status_t DoublyLinkedList_getTail(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node)
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    *node = list->head ? list->head->prev : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getNext(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || ((*node)->list != list))
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    *node = ((*node)->next != list->head) ? (*node)->next : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getPrev(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || ((*node)->list != list))
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    *node = (*node != list->head) ? (*node)->prev : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getData(const DoublyLinkedListNode_t *node, void **data)
{
#ifdef C_DATABASES_SAFE_MODE
    if (!node || !data)
        return ERR_BAD_ARGUMENT;
#endif // C_DATABASES_SAFE_MODE

    *data = node->data;

    return SUCCESS;
}
