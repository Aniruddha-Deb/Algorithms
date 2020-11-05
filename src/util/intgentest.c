#include "intgen.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int size = 20;
	int *arr = gen_ints(size, 0, size*2, 0.8);
	for (int i=0; i<size; i++) {
		printf("%d\n", arr[i]);
	}
	free(arr);
}
