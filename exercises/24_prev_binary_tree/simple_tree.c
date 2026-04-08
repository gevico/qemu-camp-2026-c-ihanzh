#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->tree_node = tree_node;
    node->next = NULL;
    if (q->front == NULL) {
        q->front = node;
        q->rear = node;
        return;
    }
    QueueNode* tail = q->rear;
    tail->next = node;
    q->rear = node;
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    QueueNode * head = q->front;
    q->front = head->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    TreeNode *tree_node = head->tree_node;
    free(head);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }

    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        return NULL;
    }
    root->val = level_order[0];
    root->left = root->right = NULL;

    Queue *q = create_queue();
    enqueue(q, root);

    int index = 1;
    while (index < size && !is_empty(q)) {
        TreeNode *node = dequeue(q);
        if (node == NULL) {
            break;
        }

        if (index < size && level_order[index] != INT_MIN) {
            TreeNode *left = (TreeNode*)malloc(sizeof(TreeNode));
            if (left == NULL) {
                free_queue(q);
                return root;
            }
            left->val = level_order[index];
            left->left = left->right = NULL;
            node->left = left;
            enqueue(q, left);
        }
        index++;

        if (index < size && level_order[index] != INT_MIN) {
            TreeNode *right = (TreeNode*)malloc(sizeof(TreeNode));
            if (right == NULL) {
                free_queue(q);
                return root;
            }
            right->val = level_order[index];
            right->left = right->right = NULL;
            node->right = right;
            enqueue(q, right);
        }
        index++;
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root == NULL) {
        return;
    }

    int capacity = 16;
    int top = 0;
    TreeNode **stack = (TreeNode**)malloc(sizeof(TreeNode*) * capacity);
    if (stack == NULL) {
        return;
    }

    stack[top++] = root;
    while (top > 0) {
        TreeNode *node = stack[--top];
        printf("%d ", node->val);
        if (node->right != NULL) {
            stack[top++] = node->right;
        }
        if (node->left != NULL) {
            stack[top++] = node->left;
        }
    }
    free(stack);
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
