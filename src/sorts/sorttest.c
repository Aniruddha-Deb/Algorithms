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
	
	ArrayList *sortList = new_ArrayList();
	ArrayList_add(sortList, &(selection_sort));

	DataSet *ds = new_DataSet("Selection Sort");
	bool err = false;
	for (int c=50; c<=5000; c+=50) {
		log_debug("Creating random array of size %d\n", c);
		int *ranarr = gen_ints(c, LBOUND, UBOUND, 0.8);
		for (int i=0; i<sortList->head; i++) {
			log_debug("allocating array of size %d\n", c);
			int *arr = malloc(sizeof(int)*c);
			memcpy(arr, ranarr, c);
			void (*sort)(int, int*) = ArrayList_get(sortList, i);
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
				DataSet_add(ds, new_Point(c, time_spent));
			}
			free(arr);
		}
		free(ranarr);
		if (err) break;
	}
	if (!err) {
		plot(ds, "Selection Sort");
	}
	destroy_DataSet(ds);
	destroy_ArrayList(sortList);
	return 0;
}
