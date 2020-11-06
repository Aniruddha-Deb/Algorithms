#include "plotter.h"
#include "../util/ds.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

DataSet* new_DataSet(ArrayList *ptList, char *name) {
	DataSet *ds = malloc(sizeof(DataSet));
	ds->ptList = ptList;
	ds->name = name;
	return ds;
}

DataSet* destroy_DataSet(DataSet *ds) {
	for (int i=0; i<ds->ptList->head; i++) {
		destroy_Point((Point*)ds->ptList[i]);
	}
	destroy_ArrayList(ds->ptList);
	free(ds);
}

Point* new_Point(int x, int y) {
	Point *p = malloc(sizeof(Point));
	p->x = x;
	p->y = y;
	return p;
}

void destroy_Point(Point *p) {
	free(p);
}

void plot(DataSet *set) {
	// plot here
}

void plotAll(int nsets, DataSet **sets) {
	// plot all here
}
