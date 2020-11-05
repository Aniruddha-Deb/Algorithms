#include "ds.h"
#include <stdio.h>

int main(int argc, char **argv) {
	ArrayList *list = new_ArrayList();

	int t;
	do {
		int *k = malloc(sizeof(int));
		scanf("%d", k);
		t = *k;
		ArrayList_add(list, k);
	} while (t != -1);

	for (int i=0; i<list->head; i++) {
		printf("%d\n", *((int*)ArrayList_get(list, i)));
	}
	
	destroy_ArrayList(list);
}
