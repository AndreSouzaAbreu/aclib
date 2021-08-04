#include "Queue.c"
#include "Iterator.c"
#include <stdio.h>
#define MAX_CHAR 256

int main()
{
  int v, n, i;
	char *s = malloc(sizeof(char) * MAX_CHAR);
  Queue* q = Queue_create(sizeof(s));
  scanf("%d", &n);

  for (i = 0; i < n; i++)
	{
    scanf("%s", s);
    Queue_enqueue(q, s);
  }

	Iterator* it = Queue_iterator(q);
	while (Iterator_hasNext(it))
	{
		Iterator_next(it, s);
		printf("s is %s\n", s);
	}

	Iterator_destroy(it);
  Queue_destroy(q);

  return 0;
}
