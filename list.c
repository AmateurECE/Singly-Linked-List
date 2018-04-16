/******************************************************************************
 * NAME:	    list.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    The file defining the API functions for the types and
 *		    function prototypes in linkedlist.h, and code meant for the
 *		    testing of those functions.
 *
 * CREATED:	    06/05/2017
 * 
 * LAST EDITED:	    04/16/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_DEBUG_LIST
#include <time.h>
#endif /* CONFIG_DEBUG_LIST */

#include "list.h"

/******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_LIST
static inline void error_exit(int, char *);
#endif /* CONFIG_DEBUG_LIST */

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:        list_create
 *
 * DESCRIPTION:     Creates a new list, and returns a pointer to it.
 *
 * ARGUMENTS:       destroy: (void (*)(void *)) -- the user-defined function
 *                           for freeing data contained in the list.
 *
 * RETURN:          (list *) -- pointer to the new list, or NULL if there was
 *		    an error.
 *
 * NOTES:           O(1)
 ***/
list * list_create(void (*destroy)(void *))
{
  list * slist = NULL;
  if ((slist = malloc(sizeof(list))) == NULL)
    return NULL;
  
  slist->size = 0;
  slist->destroy = destroy;
  slist->head = NULL;
  slist->tail = NULL;

  return slist;
}

/******************************************************************************
 * FUNCTION:        list_insnxt
 *
 * DESCRIPTION:     Inserts a new listelmt after the listelmt specified.
 *
 * ARGUMENTS:       list: (list *) -- the list to be operated on.
 *                  node: (listelmt *) -- the reference listelmt; new
 *                        listelmt is inserted after this node.
 *                  data: (const void *) -- the data to be placed in the new
 *                        listelmt.
 *
 * RETURN:          int -- -1 for failure, 0 for success.
 *
 * NOTES:           O(1)
 ***/
int list_insnxt(list * list, listelmt * node, const void * data)
{
  listelmt * new;
  
  /* Perform null check on allocated memory */
  if ((new = (listelmt *)malloc(sizeof(listelmt))) == NULL)
    return -1;

  new->data = (void *)data;

  /* Handle insertion of element at Head */
  if (node == NULL) {
    if (list_size(list) == 0)
      list->tail = new;

    new->next = list->head;
    list->head = new;
  
    /* Handle insertion somewhere else */
  } else {
    if (list_next(node) == NULL)
      list->tail = new;

    new->next = node->next;
    node->next = new;
  }
  
  list->size++;
  return 0;
}

/******************************************************************************
 * FUNCTION:        list_remnxt
 *
 * DESCRIPTION:     Removes the element after the listelmt specified.
 *
 * ARGUMENTS:       list: (list *) -- the list to be operated on.
 *                  node: (listelmt *) -- the reference listelmt; old listelmt
 *                        is removed after this node.
 *                  data: (void **) -- location for the data to be placed in
 *                        after removing the node.
 *
 * RETURN:          int -- -1 for failure, 0 for success.
 *
 * NOTES:           O(1)
 ***/
int list_remnxt(list * list, listelmt * node, void ** data)
{
  if (list_istail(list, node) || list_size(list) == 0)
    return -1;
  
  listelmt * old;

  /* Handle deletion at the head */
  if (node == NULL) {
    old = list->head;
    list->head = list->head->next;
    *data = old->data;

    /* Handle deletion somewhere else in the list */
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

/******************************************************************************
 * FUNCTION:        list_traverse
 *
 * DESCRIPTION:     Traverses the list from end to end and invokes func().
 *
 * ARGUMENTS:       llist: (list *) -- the list to be operated on.
 *                  func: (void (*)(void *)) -- the function to call on
 *                        each data point.
 *
 * RETURN:          void
 *
 * NOTES:           O(1)
 ***/
void list_traverse(list * llist, void (*func)(void *))
{
  for (listelmt * elm = list_head(llist);
       elm != NULL;
       elm = list_next(elm)) {
    func(elm->data);
  }
}

/******************************************************************************
 * FUNCTION:        list_destroy
 *
 * DESCRIPTION:     Clears the memory inhabited by a list and sets all bytes 0.
 *
 * ARGUMENTS:       list: (list **) -- the list to be operated on.
 *
 * RETURN:          void.
 *
 * NOTES:           O(n)
 ***/
void list_destroy(list ** list)
{
  if ((*list)->destroy == NULL)
    return;

  void * data = NULL;
  while (!list_remnxt(*list, NULL, (void **)&data))
    (*list)->destroy(data);

  free(*list);
  *list = NULL;
  return;
}

/******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_LIST
int main()
{  
  /* TODO: Rework testing
   */

  list * list = NULL;
  int * pNum;
  
  /* Initialize the list */
  if ((list = list_create(free)) == NULL)
    error_exit(1, "Could not create the list.");

  srand((unsigned)time(NULL));

  printf("Tail test:\n");
  /* Add ten random digits to the TAIL of thelist. */
  for (int i = 0; i < 10; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, list_tail(list), pNum);
  }

  /* Remove and print each element from the list, starting at HEAD. */
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }
  
  list_destroy(&list);
  list = list_create(free);

  printf("\nHead test:\n");
  /* Add ten random digits to the HEAD of thelist. */
  for (int i = 0; i < 10; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, NULL, pNum);
  }

  /* Remove and print each element from the list, starting at HEAD. */
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }

  list_destroy(&list);
  list = list_create(free);

  pNum = malloc(sizeof(int));
  *pNum = rand() % 20;
  list_insnxt(list, list_head(list), pNum);

  printf("\nRandom test:\n");
  /* Add ten random digits to the HEAD of thelist. */
  for (int i = 0; i < 9; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, list_tail(list), pNum);
  }

  /* Remove and print each element from the list, starting at HEAD. */
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }

  list_destroy(&list);

  printf("\n");
  return 0;
}
#endif /* CONFIG_DEBUG_LIST */

/******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_LIST
static inline void error_exit(int status, char * msg)
{
  fprintf(stderr, "%s", msg);
  exit(status);
  return;
}
#endif

/*****************************************************************************/
