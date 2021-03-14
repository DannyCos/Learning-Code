#include <stdio.h>

typedef struct Node {
  struct Node *prev;
  struct Node *next;
  int data;
} Node;

typedef struct DoublyLinkedList {
  struct Node *head;
} DoublyLinkedList;

DoublyLinkedList create_list(Node *head) {
  DoublyLinkedList list;
  list.head = head;
  return list;
}

Node create_node(int data) {
  Node node;
  node.data = data;
  node.next = NULL;
  node.prev = NULL;
  return node;
}

void add_node(DoublyLinkedList *list, Node *node) {
  Node *walk = list->head;
  while(walk->next) {
    walk = walk->next;
  }
  walk->next = node;
  node->prev = walk;
}

void print_list(DoublyLinkedList *list) {
  Node *walk = list->head;
  while(walk) {
    printf("%i ", walk->data);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  Node head = create_node(1);
  DoublyLinkedList list = create_list(&head);

  print_list(&list);
  
}
