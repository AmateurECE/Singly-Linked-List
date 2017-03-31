/*
 * TITLE: linkedlist.h
 * AUTHOR: Ethan Twardy
 * CREATED: 03.29.17
 * LAST EDITED: 03.30.17
 *
 * DESCRIPTION: The header file containing the actual
 * custom implementation of a singly-linked list
 */

#ifndef __ET_LINKEDLIST__
#define __ET_LINKEDLIST__

#include <stdlib.h>
#include <string.h>

/************* TYPE DEFINITIONS *************/
/********************************************/

typedef struct _Node_ {
  
  void * data;
  struct _Node_ * next;

} Node;

typedef struct _List_ {

  int size;
  void (*destroy)(void * data);
  Node * head;
  Node * tail;

} List;

/************* MACRO DEFINITIONS ************/
/********************************************/

// These variadic macros are pretty self explanatory.
// The complexity for all of these operations is O(1)
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#define list_isempty(list) ((list)->size == 0 ? 1 : 0)
#define list_ishead(list, element) ((list)->head == element ? 1 : 0)
#define list_istail(list, element) ((list)->tail == NULL ? 1 : 0)

/************* PUBLIC INTERFACE ************/
/*******************************************/

// FUNCTION: list_init O(1) -- initializes a list pointer
// PARAMETERS: list: List* -- the list to be operated on
//             destroy: function* -- the user-defined function for freeing the data
// RETURN: void
void list_init(List * list, void (*destroy)(void * data))
{

  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;

  return;
}

// FUNCTION: list_insnxt O(1) -- inserts a new node after the node specified
// PARAMETERS: list: List* -- the list to be operated on
//             node: Node* -- the reference node; new node is inserted after this
//             data: const void* -- the data to be placed in the new node
// RETURN: int -- -1 for failure, 0 for success
int list_insnxt(List * list, Node * node, const void * data)
{
  Node * new;
  
  // Perform null check on allocated memory
  if ((new = (Node *)malloc(sizeof(Node))) == NULL)
    return -1;

  new->data = (void *)data;

  // Handle insertion of element at Head
  if (node == NULL) {
    if (list_size(list) == 0)
      list->tail = new;

    new->next = list->head;
    list->head = new;
  
    // Handle insertion somewhere else
  } else {
    if (list_next(node) == NULL)
      list->tail = new;

    new->next = node->next;
    node->next = new;
  }
  
  list->size++;
  return 0;
}

// FUNCTION: list_remnxt O(1) -- removes the element after the node specified
// PARAMETERS: list: List* -- the list to be operated on
//             node: Node* -- the reference node; the node after this node is removed
//             data: void ** -- the data (void *) of the removed node is placed in this pointer
int list_remnxt(List * list, Node * node, void ** data)
{
  if (list_istail(list, node) || list_size(list) == 0)
    return -1;
  
  Node * old;

  // Handle deletion at the head
  if (node == NULL) {
    old = list->head;
    list->head = list->head->next;
    *data = old->data;

    // Handle deletion somewhere else in the list
  } else {
    if (list_istail(list, list_next(node)))
      list->tail = node;

    old = node->next;
    node->next = node->next->next;
    *data = old->data;
  }

  list->size--;
  free(old);
  return 0;
}

// FUNCTION: list_dest O(n) -- clears a list's memory
// PARAMETER: list: List* -- the list to be cleared
// RETURN: int -- -1 for failure, 0 for success
int list_dest(List * list)
{
  if (list->destroy == NULL)
    return -1;

  void * data;

  while (list_size(list) > 0) {
    if (list_remnxt(list, NULL, (void **)&data) == 0) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(List));
  return 0;
}

#endif // __ET_LINKEDLIST__