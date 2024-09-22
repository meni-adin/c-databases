
#include "doubly_linked_list.h"

#include <stdlib.h>

#include "errors.h"

typedef struct DoublyLinkedListNode_t_ DoublyLinkedListNode_t;

struct DoublyLinkedListNode_t_ {
    DoublyLinkedListNode_t *prev;
    DoublyLinkedListNode_t *next;
    void                   *data;
#ifdef C_DATABASES_SAFE_MODE
    DoublyLinkedList_t *list;
#endif  // C_DATABASES_SAFE_MODE
};

struct DoublyLinkedList_t_ {
    DoublyLinkedListNode_t *head;
};

#ifdef C_DATABASES_SAFE_MODE
# define DOUBLY_LINKED_LIST_DIRECTION_IS_VALID(direction) \
     (((direction) == DOUBLY_LINKED_LIST_DIRECTION_HEAD) || ((direction) == DOUBLY_LINKED_LIST_DIRECTION_TAIL))
#endif  // C_DATABASES_SAFE_MODE

static inline void DoublyLinkedList_insertNodeBefore(DoublyLinkedListNode_t *reference,
                                                     DoublyLinkedListNode_t *newNode) {
    newNode->prev       = reference->prev;
    newNode->next       = reference;
    newNode->prev->next = newNode->next->prev = newNode;
}
#include <stdlib.h>
#include <stdio.h>
status_t DoublyLinkedList_newList(DoublyLinkedList_t **list) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE
    int *arr = malloc(10 * sizeof(int));
    free(arr);
    printf("%d\n", arr[0]);
    DoublyLinkedList_t *newList = malloc(sizeof(*newList));
    if (!newList) {
        return ERR_MEM_ALLOC;
    }

    *newList = (DoublyLinkedList_t){
        .head = NULL,
    };
    *list = newList;

    return SUCCESS;
}

status_t DoublyLinkedList_deleteList(DoublyLinkedList_t *list, DoublyLinkedListDataDestructor_t destructor) {
    DoublyLinkedListNode_t *currentNode, *nextNode;
#ifdef C_DATABASES_SAFE_MODE
    if (!list) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (list->head) {
        list->head->prev->next = NULL;
        for (currentNode = list->head; currentNode != NULL; currentNode = nextNode) {
            nextNode = currentNode->next;
            destructor ? destructor(currentNode->data) : (void)destructor;
#ifdef C_DATABASES_SAFE_MODE
            *currentNode = (DoublyLinkedListNode_t){0};
#endif  // C_DATABASES_SAFE_MODE
            free(currentNode);
        }
    }

#ifdef C_DATABASES_SAFE_MODE
    *list = (DoublyLinkedList_t){0};
#endif  // C_DATABASES_SAFE_MODE
    free(list);

    return SUCCESS;
}

status_t DoublyLinkedList_insertNode(DoublyLinkedList_t           *list,
                                     const DoublyLinkedListNode_t *reference,
                                     DoublyLinkedListDirection_t   direction,
                                     void                         *data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !DOUBLY_LINKED_LIST_DIRECTION_IS_VALID(direction)) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    DoublyLinkedListNode_t *newNode = malloc(sizeof(*newNode));

    if (!newNode) {
        return ERR_MEM_ALLOC;
    }

    newNode->data = data;
#ifdef C_DATABASES_SAFE_MODE
    newNode->list = list;
#endif  // C_DATABASES_SAFE_MODE

    if (!list->head) {
        newNode->prev = newNode->next = newNode;
        list->head                    = newNode;
    } else {
        if (!reference) {
            DoublyLinkedList_insertNodeBefore(list->head, newNode);
            if (direction == DOUBLY_LINKED_LIST_DIRECTION_HEAD) {
                list->head = newNode;
            }
        } else {
            if (direction == DOUBLY_LINKED_LIST_DIRECTION_HEAD) {
                DoublyLinkedList_insertNodeBefore((DoublyLinkedListNode_t *)reference, newNode);
                if (reference == list->head) {
                    list->head = newNode;
                }
            } else {
                DoublyLinkedList_insertNodeBefore(reference->next, newNode);
            }
        }
    }

    return SUCCESS;
}

status_t DoublyLinkedList_removeNode(DoublyLinkedList_t *list, DoublyLinkedListNode_t *node) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || (node->list != list)) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (list->head == node) {
        list->head = node->next;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;
#ifdef C_DATABASES_SAFE_MODE
    *node = (DoublyLinkedListNode_t){0};
#endif  // C_DATABASES_SAFE_MODE
    free(node);

    return SUCCESS;
}

status_t DoublyLinkedList_getHead(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *node = list->head;

    return SUCCESS;
}

status_t DoublyLinkedList_getTail(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *node = list->head ? list->head->prev : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getNext(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || ((*node)->list != list)) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *node = ((*node)->next != list->head) ? (*node)->next : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getPrev(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || ((*node)->list != list)) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *node = (*node != list->head) ? (*node)->prev : NULL;

    return SUCCESS;
}

status_t DoublyLinkedList_getData(const DoublyLinkedListNode_t *node, void **data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!node || !data) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *data = node->data;

    return SUCCESS;
}

status_t DoublyLinkedList_findData(const DoublyLinkedList_t        *list,
                                   DoublyLinkedListNode_t         **node,
                                   DoublyLinkedListDirection_t      direction,
                                   DoublyLinkedListDataComparator_t comparator,
                                   const void                      *data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!list || !node || (*node && list != (*node)->list) || !DOUBLY_LINKED_LIST_DIRECTION_IS_VALID(direction) || !comparator) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    DoublyLinkedListNode_t *current, *last;

    if (!list->head) {
        *node = NULL;
        return SUCCESS;
    }

    if (direction == DOUBLY_LINKED_LIST_DIRECTION_TAIL) {
        current = last = list->head;
    } else {
        current = last = list->head->prev;
    }

    if (*node) {
        if (direction == DOUBLY_LINKED_LIST_DIRECTION_TAIL) {
            if (*node == list->head->prev) {
                *node = NULL;
                return SUCCESS;
            } else {
                current = (*node)->next;
            }
        } else if (*node == list->head) {
            *node = NULL;
            return SUCCESS;
        } else {
            current = (*node)->prev;
        }
    }

    do {
        if (comparator(data, current->data) == 0) {
            *node = current;
            return SUCCESS;
        }
        current = (direction == DOUBLY_LINKED_LIST_DIRECTION_TAIL) ? current->next : current->prev;
    } while (current != last);

    *node = NULL;
    return SUCCESS;
}
