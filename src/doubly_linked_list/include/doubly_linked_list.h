
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "c_databases_config.h"
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef enum DoublyLinkedListDirection_t_ {
    DOUBLY_LINKED_LIST_DIRECTION_HEAD,
    DOUBLY_LINKED_LIST_DIRECTION_TAIL,
} DoublyLinkedListDirection_t;

typedef struct DoublyLinkedList_t_ DoublyLinkedList_t;

typedef struct DoublyLinkedListNode_t_ DoublyLinkedListNode_t;

typedef void (*DoublyLinkedListDataDestructor_t)(void *data);

typedef int (*DoublyLinkedListDataComparator_t)(const void *data1, const void *data2);

status_t DoublyLinkedList_newList(DoublyLinkedList_t **list);

status_t DoublyLinkedList_deleteList(DoublyLinkedList_t *list, DoublyLinkedListDataDestructor_t destructor);

status_t DoublyLinkedList_insertNode(DoublyLinkedList_t           *list,
                                     const DoublyLinkedListNode_t *reference,
                                     DoublyLinkedListDirection_t   direction,
                                     void                         *data);

status_t DoublyLinkedList_removeNode(DoublyLinkedList_t *list, DoublyLinkedListNode_t *node);

status_t DoublyLinkedList_getHead(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node);

status_t DoublyLinkedList_getTail(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node);

status_t DoublyLinkedList_getNext(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node);

status_t DoublyLinkedList_getPrev(const DoublyLinkedList_t *list, DoublyLinkedListNode_t **node);

status_t DoublyLinkedList_getData(const DoublyLinkedListNode_t *node, void **data);

status_t DoublyLinkedList_findData(const DoublyLinkedList_t        *list,
                                   DoublyLinkedListNode_t         **node,
                                   DoublyLinkedListDirection_t      direction,
                                   DoublyLinkedListDataComparator_t comparator,
                                   const void                      *data);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DOUBLY_LINKED_LIST_H
