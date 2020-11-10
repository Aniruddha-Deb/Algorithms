#include "intgen.h"
#include "logger.h"
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MULTIPLIER 2
#define RANDOM_MAX 2147483647
#define WORD_BITS (8*sizeof(unsigned int))

typedef struct IntPQ {
	int *arr;
	unsigned int *emap;
	size_t emap_size;
	int emap_lb;
	size_t size;
	size_t head;
} IntPQ;

void set_bit(unsigned int *bits, size_t idx) {
	bits[idx/WORD_BITS] |= (1 << (idx % WORD_BITS));
}

int get_bit(unsigned int *bits, size_t idx) {
	return bits[idx/WORD_BITS] & (1 << (idx % WORD_BITS));
}

IntPQ* new_IntPQ(int lb, int ub) {
	IntPQ *ipq = malloc(sizeof(IntPQ));
	ipq->size = 11;
	ipq->head = 0;
	ipq->arr = malloc(sizeof(int)*ipq->size);
	ipq->emap_size = ub-lb+1;
	ipq->emap_lb = lb;
	ipq->emap = calloc(ipq->emap_size/8 + 1, sizeof(unsigned int));
	return ipq;
}

void destroy_IntPQ(IntPQ *ipq) {
	free(ipq->arr);
	free(ipq->emap);
	free(ipq);
}

void IntPQ_insert(IntPQ *ipq, int element) {
	if (ipq->head+1 >= ipq->size) {
		ipq->size *= MULTIPLIER;
		ipq->arr = realloc(ipq->arr, sizeof(int)*ipq->size);
	}
	ipq->arr[++ipq->head] = element;
	if (element >= ipq->emap_lb && element <= ipq->emap_lb+ipq->emap_size+1) {
		set_bit(ipq->emap, element-ipq->emap_lb);
	}
	int k = ipq->head;
	// swim element up
	while (k > 1 && ipq->arr[k/2] > ipq->arr[k]) {
		int temp = ipq->arr[k/2];
		ipq->arr[k/2] = ipq->arr[k];
		ipq->arr[k] = temp;
		k /= 2;
	}
}

int IntPQ_remove(IntPQ *ipq) {
	if (ipq->head < 1) {
		log_debug("Stack is empty\n");
		return -1;
	}
	int min = ipq->arr[1];
	ipq->arr[1] = ipq->arr[ipq->head--];
	// sink first element
	int k = 1;
	while (2*k <= ipq->head) {
		int j = 2*k;
		if (j <= ipq->head-1 && ipq->arr[j] > ipq->arr[j+1]) j++;
		if (ipq->arr[k] < ipq->arr[j]) break;
		int temp = ipq->arr[k];
		ipq->arr[k] = ipq->arr[j];
		ipq->arr[j] = temp;
		k = j;
	}
	return min;
}

void countInvs(int size, int *a, long invs) {
	long ninvs = 0;
	for (int i=0; i<size; i++) {
		for (int j=i+1; j<size; j++) {
			if (a[i] > a[j]) ninvs++;
		}
	}
	assert(invs == ninvs);
	log_debug("Inversions %ld equals requirement\n", invs);
}

void permute(int size, int *A, double inversions) {
	long maxInvs = size*(size-1)/2;
	long invs = inversions*maxInvs;
	int m = (int)((sqrt(8*invs+1)+1)/2);
	for (int i=0; i<m/2; i++) {
		int temp = A[i];
		A[i] = A[m-1-i];
		A[m-1-i] = temp;
	}
	int key = A[size-1];
	int left = (int)(invs-m*(m-1)/2);
	// edge case that left > size; program will just segfault in this case
	// I'll have to prove that for all m, size, invs in N, this does not happen.
	for (int i=size-1; i>=size-1-left; i--) {
		A[i] = A[i-1];
	}
	A[size-1-left] = key;

	//#ifdef DEBUG
	//countInvs(size, A, invs);
	//#endif
}

int gen_int(int lb, int ub) {
	return (int)(((double)random())/RANDOM_MAX*(ub-lb) + lb);
}

int* gen_ints(int size, int lb, int ub, double inversions) {
	IntPQ *ipq = new_IntPQ(lb, ub);
	for (int i=0; i<size; i++) {
		int rand = gen_int(lb, ub);
		while (get_bit(ipq->emap, rand-lb) > 0) {
			rand = gen_int(lb, ub);
		} 
		IntPQ_insert(ipq, rand);
	}
	int *a = malloc(sizeof(int)*size);
	for (int i=0; i<size; i++) {
		a[i] = IntPQ_remove(ipq);
	}
	destroy_IntPQ(ipq);
	permute(size, a, inversions);
	return a;
}
