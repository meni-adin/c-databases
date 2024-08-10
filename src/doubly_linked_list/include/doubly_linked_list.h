
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum DoublyLinkedListDirection_t_
{
    DOUBLY_LINKED_LIST_DIRECTION_HEAD,
    DOUBLY_LINKED_LIST_DIRECTION_TAIL,
} DoublyLinkedListDirection_t;

typedef struct DoublyLinkedList_t_ DoublyLinkedList_t;

typedef struct DoublyLinkedListNode_t_ DoublyLinkedListNode_t;

status_t DoublyLinkedList_newList(DoublyLinkedList_t **list);

status_t DoublyLinkedList_deleteList(DoublyLinkedList_t *list);

status_t DoublyLinkedList_insertNode(DoublyLinkedList_t *list, const DoublyLinkedListNode_t *reference, DoublyLinkedListDirection_t, void *data);

status_t DoublyLinkedList_removeNode(DoublyLinkedList_t *list, DoublyLinkedListNode_t *node);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DOUBLY_LINKED_LIST_H
