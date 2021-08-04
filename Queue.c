#include "Queue.h"
#include "Iterator.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* private function start with __ */
struct QueueIterator
{
  unsigned int current;
  unsigned int last;
  size_t item_size;
  QueueItem** items;
};

typedef struct QueueIterator QueueIterator;

void __QueueItem_destroy(QueueItem* n);
QueueItem* __QueueItem_create(Queue* q, void* v);
bool __Queue_iteratorHasNext(Iterator* it);
void __Queue_iteratorNext(Iterator* it, void* item);
void __Queue_iteratorDestroy(Iterator* it);

Queue* Queue_create(size_t item_size)
{
  Queue* q = malloc(sizeof(Queue));
  q->size = 0;
  q->item_size = item_size;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void Queue_destroy(Queue* q)
{
  Queue_clear(q);
  free(q);
}

void Queue_clear(Queue* q)
{
  while (q->size > 0) Queue_dequeueIt(q);
}

void Queue_enqueue(Queue* q, void* item)
{
  QueueItem* n = __QueueItem_create(q, item);
  if (q->tail == NULL)
  {
    q->head = q->tail = n;
  } else {
    q->tail->next = n;
    q->tail = n;
  }
  q->size += 1;
}

void Queue_dequeueIt(Queue* q)
{
  QueueItem* h = q->head->next;
  __QueueItem_destroy(q->head);
  q->head = h;
  q->size -= 1;
}

void Queue_dequeue(Queue* q, void* head)
{
  if (q->head == NULL) return;
  memcpy(head, q->head->item, q->item_size);
  Queue_dequeueIt(q);
}

void Queue_tail(Queue* q, void* tail)
{
  if (q->tail == NULL) return;
  memcpy(tail, q->tail->item, q->item_size);
}

void Queue_head(Queue* q, void* head)
{
  if (q->head == NULL) return;
  memcpy(head, q->tail->item, q->item_size);
}

unsigned int Queue_size(Queue* q)
{
  return q->size;
}

bool Queue_isEmpty(Queue* q)
{
  return (q->size == 0);
}

bool Queue_isNotEmpty(Queue* q)
{
  return (q->size > 0);
}

/* iterator */

Iterator* Queue_iterator(Queue* q)
{
  if (q->size == 0) return NULL;

  int i;
  Iterator* it = Iterator_create();
  QueueItem** items = malloc(q->size*sizeof(QueueItem*));
  QueueItem* item = q->head;

  for (i = 0; i < q->size; i++)
  {
    items[i] = item;
    item = item->next;
  }

  QueueIterator* qit = malloc(sizeof(QueueIterator));
  qit->items = items;
  qit->current = 0;
  qit->last = q->size - 1;
  qit->item_size = q->item_size;

  it->it = qit;
  it->next    = __Queue_iteratorNext;
  it->hasNext = __Queue_iteratorHasNext;
  it->destroy = __Queue_iteratorDestroy;
  return it;
}

bool __Queue_iteratorHasNext(Iterator* it)
{
  QueueIterator* qit = it->it;
  return qit->current <= qit->last;
}

void __Queue_iteratorNext(Iterator* it, void* item)
{
  QueueIterator* qIt = it->it;
  QueueItem* qItem = qIt->items[qIt->current];
  memcpy(item, qItem->item, qIt->item_size);
  qIt->current++;
}

void __Queue_iteratorDestroy(Iterator* it)
{
  QueueIterator* qIt = it->it;
  /* free(qIt->items); */ /* this has caused some bugs idk why */
  free(qIt);
  free(it);
}

/* private helpers */

void __QueueItem_destroy(QueueItem* n)
{
  free(n->item);
  free(n);
}

QueueItem* __QueueItem_create(Queue* q, void* item)
{
  QueueItem* n = malloc(sizeof(QueueItem));
  n->item = malloc(sizeof(q->item_size));
  memcpy(n->item, item, q->item_size);
  n->next = NULL;
  return n;
}
