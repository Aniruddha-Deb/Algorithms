#include "sorts.h"
#include "../util/gen.h"

#include <stdbool.h>

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
		int j = i;
		while (j>0 && k < A[j]) {
			A[j] = A[j-1];
			j--;
		}
		A[j] = k;
	}
}

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
