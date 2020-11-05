#include "ds.h"
#include <stdio.h>
#include "logger.h"

////////////////////////////////////////////////////////////////////////////////
//
// ArrayList functions
//
////////////////////////////////////////////////////////////////////////////////

ArrayList* new_ArrayList() {
	ArrayList *list = malloc(sizeof(ArrayList));
	list->capacity = 10;
	list->head = 0;
	list->data = malloc(sizeof(void*)*list->capacity);
	return list;
}

void _ArrayList_expand(ArrayList *list) {
	list->capacity *= MULTIPLIER;
	list->data = realloc(list->data, sizeof(void*)*list->capacity);
}

void destroy_ArrayList(ArrayList *list) {
	free(list->data);
	free(list);
}

int ArrayList_add(ArrayList *list, void *elem) {
	if (list->head >= list->capacity) {
		_ArrayList_expand(list);
		if (list->data == NULL) return ERR;
	}
	list->data[list->head++] = elem;
	log_debug("Added element at %d\n", (int)list->head-1);
	return OK;
}

void* ArrayList_get(ArrayList *list, int index) {
	if (index < 0 || index >= list->head) return NULL;
	log_debug("Getting element at %d\n", index);
	return list->data[index];
}

void* ArrayList_remove(ArrayList *list, int index) {
	if (index < 0 || index >= list->head) return NULL;
	void *elem = list->data[index];
	for (int i=index; i<list->head-1; i++) {
		list->data[i] = list->data[i+1];
	}
	list->head--;
	return elem;
}

void* ArrayList_set(ArrayList *list, int index, void *elem) {
	if (index < 0 || index >= list->head) return NULL;
	void *removed_elem = list->data[index];
	list->data[index] = elem;
	return removed_elem;
}

int ArrayList_insert(ArrayList *list, int index, void *elem) {
	if (index < 0 || index > list->head) return ERR;
	if (list->head >= list->capacity) {
		_ArrayList_expand(list);
		if (list->data == NULL) return ERR;
	}
	for (int i=list->head; i>index; i--) {
		list->data[i] = list->data[i-1];
	}
	list->data[index] = elem;
	return OK;
}

////////////////////////////////////////////////////////////////////////////////
//
// Deque functions
//
////////////////////////////////////////////////////////////////////////////////
