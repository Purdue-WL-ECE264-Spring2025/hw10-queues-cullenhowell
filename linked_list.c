#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{
  struct list_node * nd = malloc(sizeof(struct list_node));
  if (nd == NULL) return NULL;
  nd -> value = value;
  nd -> next = NULL;
  return nd;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * ptr = new_node(value);
  if (ptr == NULL) return;
  ptr -> next = list -> head;
  list -> head = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node * ptr = new_node(value);
  if (ptr == NULL) return;
  if (list -> head == NULL)
  {
    list -> head = ptr;
    return;
  }
  struct list_node * current = list -> head;
  while ((current -> next) != NULL) {current = current -> next;}
  current -> next = ptr;
}

size_t remove_from_head(struct linked_list *list) 
{
  if (list -> head == NULL) return 0;
  struct list_node * temp_head = list -> head;
  size_t temp_val = temp_head -> value;
  list -> head = temp_head -> next;
  free(temp_head);
  return temp_val;
}

size_t remove_from_tail(struct linked_list *list) 
{
  if (list -> head == NULL) return 0;
  if (list -> head -> next == NULL)
  {
    size_t temp_val = list -> head -> value;
    free(list -> head);
    list -> head = NULL;
    return temp_val;
  }
  struct list_node *current = list->head;
  if (current != NULL) 
  {
    while (current->next != NULL && current->next->next != NULL) {current = current->next;}
  }
  size_t temp_val = current -> next -> value;
  free(current->next);
  current -> next = NULL;
  return temp_val;
}

void free_list(struct linked_list list) 
{
  struct list_node * current = list.head;
  while (current != NULL)
  {
    struct list_node * next = current -> next;
    free(current);
    current = next;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
