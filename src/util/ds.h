#ifndef _DS_H_
#define _DS_H_

#include <stdlib.h>
#include <inttypes.h>

#define MULTIPLIER 2

#define ERR -1
#define OK 1

// ArrayList definitions //////////////////////////////////////////////////////

typedef struct ArrayList {
	void **data;
	size_t capacity;
	size_t head;
} ArrayList;

ArrayList* new_ArrayList();
void destroy_ArrayList(ArrayList *list);
int ArrayList_add(ArrayList *list, void *elem);
void* ArrayList_get(ArrayList *list, int index);
void* ArrayList_remove(ArrayList *list, int index);
void* ArrayList_set(ArrayList *list, int index, void *elem);
int ArrayList_insert(ArrayList *list, int index, void *elem);

// Deque definitions //////////////////////////////////////////////////////////

typedef struct Deque {
	void **data;
	size_t capacity;
	size_t head;
	size_t tail;
} Deque;

#endif
