#include "sorts.h"
#include "../util/gen.h"

#include <stdbool.h>
#include <stdlib.h>

Sort* new_Sort(char *name, void (*sort)(int, int*)) {
	Sort *s = malloc(sizeof(Sort));
	s->name = name;
	s->sort = sort;
	return s;
}

void destroy_Sort(Sort *sort) {
	free(sort);
}

void selection_sort(int n, int *A) {
	for (int i=0; i<n; i++) {
		int index = i;
		for (int j=i+1; j<n; j++) {
			if (A[j] < A[index]) index = j;
		}
		if (index != i)
			swap(&A[index], &A[i]);
	}
}

void bubble_sort(int n, int *A) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n-i-1; j++) {
			if (A[j] > A[j+1]) {
				swap(&A[j], &A[j+1]);
			}
		}
	}
}

void insertion_sort(int n, int *A) {
	for (int i=0; i<n; i++) {
		int k = A[i];
		int j = i-1;
		while (j>=0 && k < A[j]) {
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = k;
	}
}
/*
static void merge(int s1, int e1, int s2, int e2, int *A, int *B) {
	int l1 = e1-s1;
	int l2 = e2-s2;
	int lm = min2(l1, l2);
	for (int i=0; i<=lm; i++) {
		int min = min2(A[s1+i], A[s2+i]);
		int max = max2(A[s1+i], A[s2+i]);
		B[s1+2*i] = min;
		B[s1+2*i+1] = max;
	}
	if (l1 > l2) {
		B[e2] = A[e1];
	}
}*/
/*
static void merge_sort_recr(int start, int end, int *A, int *B) {
	if (start == end) return;
	else if (start == end-1) {
		if (A[start] <= A[end]) return;
		else swap(&A[start], &A[end]);
	}
	else {
		int s1 = start;
		int e1 = (end+start)/2;
		int s2 = e1+1;
		int e2 = end;
		merge_sort_recr(s1, e1, A, B);
		merge_sort_recr(s2, e2, A, B);
		merge(s1, e1, s2, e2, A, B);
	}
}*/

/*
void merge_sort(int n, int *A) {
	int s1 = 0;
	int e1 = n/2;
	int s2 = e1 + 1;
	int e2 = n-1;
	int *B = malloc(sizeof(int)*n);
	merge_sort_recr(s1, e1, A, B);
	merge_sort_recr(s2, e2, A, B);
	merge(s1, e1, s2, e2, A, B);
	free(A);
	A = B;
}*/

bool is_sorted_asc(int n, int *A) {
	for (int i=0; i<n-1; i++) {
		if (A[i] > A[i+1]) {
			return false;
		}
	}
	return true;
}

bool is_sorted_desc(int n, int *A) {
	for (int i=0; i<n-1; i++) {
		if (A[i] < A[i+1]) {
			return false;
		}
	}
	return true;
}
