#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    link node = (link)malloc(sizeof(struct node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    free(p);
}

link search(int key) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p != tail) {
        if (p->data == key) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    link next = head->next;
    next->prev = p;
    head->next = p;
    p->prev = head;
    p->next = next;
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    link ptr = head->next;
    while (ptr != tail) {
        if (ptr == p) {
            link next = ptr->next;
            link prev = ptr->prev;

            prev->next = next;
            next->prev = prev;
            free_node(p);
            return;
        }
        ptr = ptr->next;
    }
}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p != tail) {
        visit(p);
        p = p->next;
    }
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p != tail) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head->next = tail;
    tail->prev = head;
}
