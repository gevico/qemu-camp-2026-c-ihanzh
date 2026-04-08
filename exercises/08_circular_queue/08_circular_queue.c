#include <stdbool.h>
#include <stdio.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

static void queue_init(Queue* queue, int num) {
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    for (int i = 0; i < num; ++i) {
        queue->data[queue->tail].id = i + 1;
        queue->tail = (queue->tail + 1) % MAX_PEOPLE;
        queue->count++;
    }
}

static bool queue_empty(const Queue* queue) { return queue->count == 0; }

static int queue_size(const Queue* queue) { return queue->count; }

static People queue_pop(Queue* queue) {
    People p = queue->data[queue->head];
    queue->head = (queue->head + 1) % MAX_PEOPLE;
    queue->count--;
    return p;
}

static void queue_push(Queue* queue, People person) {
    queue->data[queue->tail] = person;
    queue->tail = (queue->tail + 1) % MAX_PEOPLE;
    queue->count++;
}

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;

    queue_init(&q, total_people);

    while (queue_size(&q) > 1) {
        for (int i = 1; i < report_interval; ++i) {
            People front = queue_pop(&q);
            queue_push(&q, front);
        }
        queue_pop(&q);
        printf("淘汰: %d\n", q.data[(q.head - 1 + MAX_PEOPLE) % MAX_PEOPLE].id);
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);
    return 0;
}
