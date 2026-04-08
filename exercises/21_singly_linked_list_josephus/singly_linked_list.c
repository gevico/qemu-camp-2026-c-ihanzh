#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    // TODO: 在这里添加你的代码
    link new_node = (link)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    // TODO: 在这里添加你的代码
    for (link p = head; p; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    // TODO: 在这里添加你的代码
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    // TODO: 在这里添加你的代码
    for (link ptr = head; ptr; ptr = ptr->next) {
        if (p == ptr->next) {
            ptr->next = p->next;
            p->next = NULL;
            free(p);
            return;
        }
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    for (link p = head; p; p = p->next) {
        visit(p);
    }
}

// 销毁整个链表
void destroy(void) {
    // TODO: 在这里添加你的代码
    free_list(head);
    head = NULL;
}

// 在链表头部推入节点
void push(link p) {
    // TODO: 在这里添加你的代码
    p->next = head;
    head = p;
}

// 从链表头部弹出节点
link pop(void) {
    // TODO: 在这里添加你的代码
    link val = head;
    head = head->next;
    val->next = NULL;
    return val;
}

// 释放链表内存
void free_list(link list_head) {
    // TODO: 在这里添加你的代码
    link p = NULL;
    while (list_head) {
        p = list_head->next;
        free(list_head);
        list_head = p;
    }
}
