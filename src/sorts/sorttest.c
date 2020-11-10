#include "sorts.h"
#include "../util/ds.h"
#include "../util/intgen.h"
#include "../util/logger.h"
#include "../ui/plotter.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define LBOUND 0
#define UBOUND 50000

int main(int argc, char **argv) {
	srandom(time(NULL));
	ArrayList *sortList = new_ArrayList();
	ArrayList_add(sortList, new_Sort("Selection Sort", &selection_sort));
	ArrayList_add(sortList, new_Sort("Insertion Sort", &insertion_sort));
	ArrayList_add(sortList, new_Sort("Bubble Sort", &bubble_sort));

	ArrayList *dataList = new_ArrayList();
	for (int i=0; i<sortList->head; i++) {
		Sort *s = sortList->data[i];
		ArrayList_add(dataList, new_DataSet(s->name));
	}
	bool err = false;
	
	for (int c=50; c<=5000; c+=50) {
		log_debug("Creating random array of size %d\n", c);
		int *ranarr = gen_ints(c, LBOUND, UBOUND, 0.8);
		for (int i=0; i<sortList->head; i++) {
			log_debug("allocating array of size %d\n", c);
			int *arr = malloc(sizeof(int)*c);
			memcpy(arr, ranarr, c);
			Sort *s = ArrayList_get(sortList, i);
			void (*sort)(int, int*) = s->sort;
			clock_t begin = clock();
			(*sort)(c, arr);
			clock_t end = clock();
			int time_spent = round(1000000.0*(end-begin)/CLOCKS_PER_SEC);
			if (!is_sorted_asc(c, arr)) {
				err = true;
				log_debug("Sort %d failed\n", i);
				free(arr);
				break;
			}
			else {
				log_debug("Sort %d passed\n", i);
				DataSet_add(dataList->data[i], new_Point(c, time_spent));
			}
			free(arr);
		}
		free(ranarr);
		if (err) break;
	}
	if (!err) {
		plotAll(dataList->head, (DataSet**)dataList->data, "Sorts - Time (us) vs Array Size");
	}
	for (int i=0; i<sortList->head; i++) {
		destroy_Sort(sortList->data[i]);
		destroy_DataSet(dataList->data[i]);
	}
	destroy_ArrayList(sortList);
	destroy_ArrayList(dataList);
	
	return 0;
}
