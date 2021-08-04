#ifndef H_Queue
#define H_Queue

#include <stdbool.h>
#include <stdlib.h>
#include "Iterator.h"

typedef struct QueueItem QueueItem;
typedef struct Queue Queue;

struct QueueItem
{
  void* item;
  QueueItem* next;
};

struct Queue
{
  unsigned int size;
  size_t item_size;
  QueueItem* head;
  QueueItem* tail;
};

Queue* Queue_create(size_t item_size);
void Queue_destroy(Queue* q);
void Queue_clear(Queue* q);
void Queue_enqueue(Queue* q, void* item);
void Queue_dequeue(Queue* q, void* head);
void Queue_dequeueIt(Queue* q);
void Queue_head(Queue* q, void* head);
void Queue_tail(Queue* q, void* tail);
Iterator* Queue_iterator(Queue* q);
unsigned int Queue_size(Queue* q);
bool Queue_isEmpty(Queue* q);
bool Queue_isNotEmpty(Queue* q);

#endif
