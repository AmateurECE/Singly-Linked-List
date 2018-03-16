/******************************************************************************
 * NAME:	    list.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    The header file containing the type definitions and
 *		    function prototypes for the implementation of a
 *		    singly-linked list.
 *
 * CREATED:	    03/29/2017
 *
 * LAST EDITED:	    03/16/2018
 */

#ifndef __ET_LIST_H__
#define __ET_LIST_H__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _listelmt_ {
  
  void * data;
  struct _listelmt_ * next;

} listelmt;

typedef struct {

  int size;
  void (*destroy)(void * data);
  listelmt * head;
  listelmt * tail;

} list;

/******************************************************************************
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

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern list * list_create(void (*destroy)(void *));
extern int list_insnxt(list * list, listelmt * elmt, const void * data);
extern int list_remnxt(list * list, listelmt * elmt, void ** data);
extern void list_traverse(list * list, void (*fn)(void *));
extern int list_destroy(list ** list);

#endif /* __ET_LIST_H__ */

/*****************************************************************************/
