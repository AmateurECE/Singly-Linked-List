/*
 * linkedlist.c
 *
 * The Test file for the custom implementation of a Linked List
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

static inline void error_exit(int status, char * msg)
{
  fprintf(stderr, "%s", msg);
  exit(status);
  return;
}

void destroy(void * data)
{
  free(data);
}

int main(int argc, char * argv[])
{  
  List * list;
  int * pNum;

  // Allocate a list, or fail if it cannot be done.
  if ((list = malloc(sizeof(List))) == NULL)
    error_exit(1, "Could not allocate storage for list!\n");
  
  // Initialize the list
  list_init(list, destroy);

  srand((unsigned)time(NULL));

  printf("Tail test:\n");
  // Add ten random digits to the TAIL of thelist.
  for (int i = 0; i < 10; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, list_tail(list), pNum);
  }

  // Remove and print each element from the list, starting at HEAD.
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }
  
  list_dest(list);
  list_init(list, destroy);

  printf("\nHead test:\n");
  // Add ten random digits to the HEAD of thelist.
  for (int i = 0; i < 10; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, NULL, pNum);
  }

  // Remove and print each element from the list, starting at HEAD.
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }

  list_dest(list);
  list_init(list, destroy);

  pNum = malloc(sizeof(int));
  *pNum = rand() % 20;
  list_insnxt(list, list_head(list), pNum);

  printf("\nRandom test:\n");
  // Add ten random digits to the HEAD of thelist.
  for (int i = 0; i < 9; i++) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 20;
    list_insnxt(list, list_tail(list), pNum);
  }

  // Remove and print each element from the list, starting at HEAD.
  while (!list_isempty(list)) {
    list_remnxt(list, NULL, (void **)&pNum);
    printf("%d ", *pNum);
    free(pNum);
  }

  list_dest(list);

  printf("\n");
  free(list);
  return 0;
}
