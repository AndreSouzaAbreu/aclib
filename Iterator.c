#include "Iterator.h"
#include <stdbool.h>
#include <stdlib.h>

Iterator* Iterator_create()
{
  return malloc(sizeof(Iterator*));
}

void Iterator_destroy(Iterator* it)
{
	it->destroy(it);
}

void Iterator_next(Iterator* it, void* next)
{
  it->next(it, next);
}

bool Iterator_hasNext(Iterator* it)
{
  return it->hasNext(it);
}
