#ifndef _PLOTTER_H_
#define _PLOTTER_H_

#include "../util/ds.h"

typedef struct Point {
	int x, y;
} Point;

typedef struct DataSet {
	ArrayList *ptList;
	int xMax, yMax;
	int xMin, yMin;
	long xMean, yMean;
	char *name;
} DataSet;

DataSet* new_DataSet(char *name);
void destroy_DataSet(DataSet *ds);
void DataSet_add(DataSet *ds, Point *pt);

Point* new_Point(int x, int y);
void destroy_Point(Point *p);

int plot(DataSet *set, char *title);
int plotAll(int nsets, DataSet **sets, char *title);

#endif
