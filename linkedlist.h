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

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _ListElm_ {
  
  void * data;
  struct _ListElm_ * next;

} ListElm;

typedef struct _List_ {

  int size;
  void (*destroy)(void * data);
  ListElm * head;
  ListElm * tail;

} List;

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#define list_isempty(list) ((list)->size == 0 ? 1 : 0)
#define list_ishead(list, element) ((list)->head == element ? 1 : 0)
#define list_istail(list, element) ((list)->tail == NULL ? 1 : 0)

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void list_init(List *, void (*)(void *));
extern int list_insnxt(List *, ListElm *, const void *);
extern int list_remnxt(List *, ListElm *, void **);
extern void list_traverse(List *, void (*)(void *));
extern int list_dest(List *);

#endif /* __ET_LINKEDLIST__ */
