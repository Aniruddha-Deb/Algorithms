#ifndef _SORTS_H_
#define _SORTS_H_

#include <stdbool.h>

typedef struct Sort {
	char *name;
	void (*sort)(int, int*);
} Sort;

Sort* new_Sort(char *name, void (*sort)(int, int*));
void destroy_Sort(Sort *sort);

void selection_sort(int n, int *A);
void bubble_sort(int n, int *A);
void insertion_sort(int n, int *A);
void merge_sort(int n, int *A);
void heap_sort(int n, int *A);

bool is_sorted_asc(int n, int *A);
bool is_sorted_desc(int n, int *A);

#endif
