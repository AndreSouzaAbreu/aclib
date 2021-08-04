#ifndef H_Iterator
#define H_Iterator

#include <stdbool.h>

typedef struct Iterator Iterator;
struct Iterator {
  void* it;
  bool (*hasNext)(Iterator* it);
  void (*next)(Iterator* it, void* next);
	void (*destroy)(Iterator* it);
};

Iterator* Iterator_create();
void Iterator_destroy(Iterator* it);
void Iterator_next(Iterator* it, void* next);
bool Iterator_hasNext(Iterator* it);

#endif
