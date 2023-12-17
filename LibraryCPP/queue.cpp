#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t last;
    size_t* first;

    Queue() {
        vector = vector_create();
        last = -1;
        first = -1;
    }
    ~Queue() {
        vector_delete(vector);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t size = vector_size(queue->vector);

    if (queue_empty(queue)) {
        queue->first = 0;
        queue->last= 0;
    }
    else if (queue->last % static_cast<int>(size) == queue->first) {
        Vector* buff = vector_create();
        vector_resize(buff, size * 2);

        int counter = 0;

        for (size_t i = queue->first; i < size; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        for (int i = 0; i < queue->rear; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        vector_delete(queue->vector);
        queue->vector = buff;
        queue->head = 0;
        queue->last = static_cast<int>(size);

        size = vector_size(queue->vector);
    }
    Data last = queue->last % size;
    vector_set(queue->vector, last, data);
    queue->last = last + 1;
}


Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) {
        return NULL;
    }
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) {
        return;
    }
    queue->first++;
}

bool queue_empty(const Queue *queue)
{
    return queue->first == queue->last;
}
