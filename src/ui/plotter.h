#ifndef _PLOTTER_H_
#define _PLOTTER_H_

#include "../util/ds.h"

typedef struct Point {
	int x, y;
} Point;

typedef struct DataSet {
	ArrayList *ptList;
	char *name;
} DataSet;

DataSet* new_DataSet(ArrayList *ptList, char *name);
void destroy_DataSet(DataSet *ds);

Point* new_Point(int x, int y);
void destroy_Point(Point *p);

void plot(DataSet *set);
void plotAll(int nsets, DataSet **sets);

#endif
