#include "plotter.h"
#include "../util/ds.h"
#include "../util/logger.h"
#include "SDL_util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 600

#define XTICKS 10
#define YTICKS 10

// constants
const SDL_Color bgColor = {0xF4, 0xF4, 0xF4, 0xFF};
const SDL_Color axisColor = {0xA5, 0xA5, 0xA5, 0xFF};
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
	ds->nxt = XTICKS;
	ds->nyt = YTICKS;
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

static int round_tr(double tr) {
	int nd = (int)(log10(tr))+1;
	double exp = pow(10, nd);
	double str = tr/exp;
	if (str <= 0.1) return round(0.1*exp);
	if (str <= 0.2) return round(0.2*exp);
	if (str <= 0.25) return round(0.25*exp);
	if (str <= 0.5) return round(0.5*exp);
	if (str <= 0.75) return round(0.75*exp);
	return round(exp);
}

void DataSet_add(DataSet *ds, Point *pt) {
	ArrayList_add(ds->ptList, pt);
	if (pt->x > ds->xMax) ds->xMax = pt->x; 
	if (pt->x < ds->xMin) ds->xMin = pt->x; 
	if (pt->y > ds->yMax) ds->yMax = pt->y; 
	if (pt->y < ds->yMin) ds->yMin = pt->y; 
	ds->xMean = (ds->xMean*ds->ptList->head + pt->x)/(ds->ptList->head+1);
	ds->yMean = (ds->yMean*ds->ptList->head + pt->y)/(ds->ptList->head+1);

	// recalculate ticks
	if (ds->xMin != ds->xMax) {
		double range = ds->xMax - ds->xMin;
		ds->xtr = round_tr(range/ds->nxt);
		ds->xlb = ds->xtr*floor(((double)ds->xMin)/ds->xtr);
	}
	if (ds->yMin != ds->yMax) {
		double range = ds->yMax - ds->yMin;
		ds->ytr = round_tr(range/ds->nyt);
		ds->ylb = ds->ytr*floor(((double)ds->yMin)/ds->ytr);
		log_debug("Recalculated y lower bound as %d\n", ds->ylb);
	}
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

int plot(DataSet *ds, char *title) {
	// Standard SDL Application structure
	if (init_graphics() == -1) return -1;
	SDL_Window *win = create_SDL_window(title, WIDTH, HEIGHT);
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
	int bry = round(0.85*HEIGHT);
	int lmark = round(0.015*HEIGHT);
	int smark = round(0.0075*HEIGHT);
	double th = (0.8/ds->nyt)*HEIGHT;
	double tw = (0.8/ds->nxt)*WIDTH;
	// gridlines
	for (int i=1; i<ds->nyt; i++) {
		int y = round(bry - th*i -1);
		SDL_RenderDrawDashedLine(renderer, tlx, y, brx, y, 10, 10);
	}
	for (int i=1; i<ds->nxt; i++) {
		int x = round(tw*i + tlx);
		SDL_RenderDrawDashedLine(renderer, x, tly, x, bry, 10, 10);
	}
	// axes
	SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	SDL_RenderDrawLine(renderer, tlx, tly, tlx, bry);
	SDL_RenderDrawLine(renderer, tlx, bry, brx, bry);
	// markings and text
	TTF_Font *opensans_12pt = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 12);
	SDL_RenderDrawLine(renderer, tlx, bry, tlx, bry+lmark);
	for (int i=0; i<ds->nxt; i++) {
		for (int j=1; j<5; j++) {
			int x = round(tlx+tw*(i+0.2*j));
			SDL_RenderDrawLine(renderer, x, bry, x, bry+smark);
		}
		int x = round(tlx + tw*(i+1));
		SDL_RenderDrawLine(renderer, x, bry, x, bry+lmark);
		SDL_SetRenderDrawColor(renderer, axisTextColor.r, axisTextColor.g, axisTextColor.b, axisTextColor.a);
		int tw=0, th=0;
		int num = ds->xlb + (i+1)*ds->xtr;
		char *s = malloc(sizeof(char)*15);
		snprintf(s, 15, "%d", num);
		if (opensans_12pt != NULL)
		TTF_SizeText(opensans_12pt, s, &tw, &th);
		else log_debug("Could not load font\n");
		SDL_RenderText(renderer, round(x-((double)tw)/2), bry+lmark+smark,
					   opensans_12pt, s);
		SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	}
	SDL_RenderDrawLine(renderer, tlx, bry, tlx-lmark, bry);
	for (int i=0; i<ds->nyt; i++) {
		for (int j=1; j<5; j++) {
			int y = round(bry-th*(i+0.2*j));
			SDL_RenderDrawLine(renderer, tlx, y, tlx-smark, y);
		}
		int y = round(bry-th*(i+1)-1);
		SDL_RenderDrawLine(renderer, tlx, y, tlx-lmark, y);
		SDL_SetRenderDrawColor(renderer, axisTextColor.r, axisTextColor.g, axisTextColor.b, axisTextColor.a);
		int tw=0, th=0;
		int num = ds->ylb + (i+1)*ds->ytr;
		char *s = malloc(sizeof(char)*15);
		snprintf(s, 15, "%d", num);
		if (opensans_12pt != NULL)
		TTF_SizeText(opensans_12pt, s, &tw, &th);
		else log_debug("Could not load font\n");
		SDL_RenderText(renderer, tlx-tw-lmark-smark, round(y-((double)th)/2),
					   opensans_12pt, s);
		SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	}
	// x axis highlight
	SDL_SetRenderDrawColor(renderer, xAxisHighlightColor.r, xAxisHighlightColor.b, xAxisHighlightColor.g, xAxisHighlightColor.a);
	SDL_RenderDrawLine(renderer, tlx, bry-1, brx, bry-1);
	// points
	SDL_SetRenderDrawColor(renderer, pointBlueColor.r, pointBlueColor.g, pointBlueColor.b, pointBlueColor.a);
	for (int i=0; i<ds->ptList->head; i++) {
		Point *p = ds->ptList->data[i];
		int px = p->x;
		int py = p->y;
		int x = tlx + round((double)(brx-tlx)*(px-ds->xlb)/(ds->xtr*ds->nxt));
		int y = bry - round((double)(bry-tly)*(py-ds->ylb)/(ds->ytr*ds->nyt));
		log_debug("Point to plot for (%d,%d) is (%d,%d)\n",px,py,x,y);
		SDL_RenderFillCircle(renderer, x, y, 5);
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
