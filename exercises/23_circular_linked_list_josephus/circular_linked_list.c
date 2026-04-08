#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node *create_circular_list(int n) {
  // TODO: 在这里添加你的代码
  Node *head = (Node *)malloc(sizeof(Node));
  head->id = 1;
  Node *cur = head;
  for (int i = 2; i <= n; ++i) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = i;
    cur->next = node;
    cur = node;
  }
  cur->next = head;
  return head;
}

void free_list(Node *head) {
  // TODO: 在这里添加你的代码
  while (1) {
    Node *next = head->next;
    if (next == head) {
      free(head);
      return;
    }
    free(head);
    head = next;
  }
}
