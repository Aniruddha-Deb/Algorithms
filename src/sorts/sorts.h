#ifndef _SORTS_H_
#define _SORTS_H_

#include <stdbool.h>

void selection_sort(int n, int *A);
void bubble_sort(int n, int *A);
void insertion_sort(int n, int *A);

bool is_sorted_asc(int n, int *A);
bool is_sorted_desc(int n, int *A);

#endif
