#include "plotter.h"
#include "../util/ds.h"
#include "SDL_util.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 1024
#define HEIGHT 768

// constants
const SDL_Color bgColor = {0xF4, 0xF4, 0xF4, 0xFF};
const SDL_Color axisColor = {0xC3, 0xC3, 0xC3, 0xFF};
const SDL_Color axisTextColor = {0x57, 0x57, 0x57, 0xFF};
const SDL_Color gridColor = {0xBB, 0xBB, 0xBB, 0xFF};
const SDL_Color labelColor = {0x32, 0x32, 0x32, 0xFF};
const SDL_Color xAxisHighlightColor = {0x63, 0x63, 0x63, 0xFF};
const SDL_Color pointBlueColor = {0x2A, 0x53, 0xDF, 0xFF};
const SDL_Color pointOrangeColor = {0xF5, 0x61, 0x1E, 0xFF};
const SDL_Color pointGreenColor = {0x53, 0xB8, 0x52, 0xFF};
const SDL_Color pointYellowColor = {0xFD, 0xA8, 0x00, 0xFF};

// Function definitions used in this file
void render_graph(SDL_Renderer *renderer);
void render_pts(SDL_Renderer *renderer, ArrayList *ptList, SDL_Color *c);

DataSet* new_DataSet(char *name) {
	DataSet *ds = malloc(sizeof(DataSet));
	ds->ptList = new_ArrayList();
	ds->xMax = ds->yMax = INT_MIN;
	ds->xMin = ds->yMin = INT_MAX;
	ds->name = name;
	return ds;
}

void destroy_DataSet(DataSet *ds) {
	for (int i=0; i<ds->ptList->head; i++) {
		destroy_Point(ds->ptList->data[i]);
	}
	destroy_ArrayList(ds->ptList);
	free(ds);
}

void DataSet_add(DataSet *ds, Point *pt) {
	ArrayList_add(ds->ptList, pt);
	if (pt->x > ds->xMax) ds->xMax = pt->x; 
	if (pt->x < ds->xMin) ds->xMin = pt->x; 
	if (pt->y > ds->yMax) ds->yMax = pt->y; 
	if (pt->y < ds->yMin) ds->yMin = pt->y; 
	ds->xMean = (ds->xMean*ds->ptList->head + pt->x)/(ds->ptList->head+1);
	ds->yMean = (ds->yMean*ds->ptList->head + pt->y)/(ds->ptList->head+1);
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

int plot(DataSet *set, char *title) {
	// Standard SDL Application structure
	if (init_graphics() == -1) return -1;
	SDL_Window *win = create_SDL_window("Scatter Chart Plotter", WIDTH, HEIGHT);
	if (win == NULL) return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
	const SDL_Rect screen = {0, 0, WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &screen);

	// draw axes; note the subpixel correct rendering
	SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
	int tlx = round(0.1*WIDTH);
	int brx = round(0.9*WIDTH);
	int tly = round(0.05*HEIGHT);
	double w = 0.08*HEIGHT;
	for (int i=1; i<=10; i++) {
		int y = round(w*i + tly);
		SDL_RenderDrawDashedLine(renderer, tlx, y, brx, y, 10, 10);
	}
	SDL_RenderPresent(renderer);

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
		}
	}
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

int plotAll(int nsets, DataSet **sets, char *title) {
	// plot all here
	return 0;
}
