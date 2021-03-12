#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

LinkedList create_linked_list(Node *head) {
  LinkedList list;
  list.head = head;
  return list;
}

Node *create_node(int data) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  return node;
}

void add_node(LinkedList *list, Node *node) {
  Node *walk = list->head;

  while(walk->next != NULL) {
    walk = walk->next;
  }

  walk->next = node;
}

void delete_node(LinkedList *list, Node *target) {
  Node **pointer = &list->head;
  while(*pointer != target) {
    pointer = &(*pointer)->next;
  }
  *pointer = target->next;
}

void replace(LinkedList *list, Node *target, Node *node) {
  node->next = target->next;
  *target = *node;
}

void insert_before(LinkedList *list, Node *target, Node *node) {
  Node **pointer = &list->head;
  while(*pointer != target) {
    pointer = &(*pointer)->next;
  }
  *pointer = node;
  node->next = target;
}

void insert_after(LinkedList *list, Node *target, Node *node) {
  node->next = target->next;
  target->next = node;
}

Node *get_index(LinkedList *list, int index) {
  Node *walk = list->head;
  while(index > 0) {
    walk = walk->next;
    index -= 1;
  }
  return walk;
}

size_t size_of_list(LinkedList *list) {
  Node *walk = list->head;
  size_t index = 0;
  while(walk) {
    index++;
    walk = walk->next;
  }
  return index;
}

void print_list(LinkedList *list) {
  Node *walk = list->head;
  while(walk != NULL) {
    printf("%i  ", walk->data);
    walk = walk->next;
  }
  printf("\n");
}
