#include "plotter.h"
#include "color.h"
#include "../util/ds.h"
#include "../util/logger.h"
#include "SDL_util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
// p_ = plot
// br = bottom right
// btl/stl = big/small tick length
int p_tlx = 80; // round(0.1*WIDTH); // tl = top left
int p_brx = 720; // round(0.9*WIDTH); // br = bottom right
int p_tly = 30; // round(0.05*HEIGHT);
int p_bry = 510; // round(0.85*HEIGHT);
int p_btl = 9; // round(0.015*HEIGHT); // big tick length
int p_stl = 6; // round(0.0075*HEIGHT); // small tick length

const SDL_Color bgColor = {0xF4, 0xF4, 0xF4, 0xFF};
const SDL_Color axisColor = {0xA5, 0xA5, 0xA5, 0xFF};
const SDL_Color axisTextColor = {0x57, 0x57, 0x57, 0xFF};
const SDL_Color gridColor = {0xBB, 0xBB, 0xBB, 0xFF};
const SDL_Color labelColor = {0x32, 0x32, 0x32, 0xFF};
const SDL_Color xAxisHighlightColor = {0x63, 0x63, 0x63, 0xFF};
const SDL_Color pointBlueColor = {0x2A, 0x53, 0xDF, 0xCF};
const SDL_Color pointOrangeColor = {0xF5, 0x61, 0x1E, 0xFF};
const SDL_Color pointGreenColor = {0x53, 0xB8, 0x52, 0xFF};
const SDL_Color pointYellowColor = {0xFD, 0xA8, 0x00, 0xFF};

static int round_tr(double tr);

typedef struct GridData {
	int xlbound, ylbound, xtickrange, ytickrange;
	int numxticks, numyticks;
} GridData;

GridData* new_GridData(int numxticks, int numyticks, int numdsets, DataSet **sets) {
	GridData *gd = malloc(sizeof(GridData));
	gd->numxticks = numxticks;
	gd->numyticks = numyticks;
	
	int xMax, yMax, xMin, yMin;
	xMax = yMax = INT_MIN;
	xMin = yMin = INT_MAX;
	for (int i=0; i<numdsets; i++) {
		DataSet *ds = sets[i];
		if (ds->xMax > xMax) xMax = ds->xMax;
		if (ds->yMax > yMax) yMax = ds->yMax;
		if (ds->xMin < xMin) xMin = ds->xMin;
		if (ds->yMin < yMin) yMin = ds->yMin;
	}
	if (xMin != xMax) {
		double range = xMax - xMin;
		gd->xtickrange = round_tr(range/numxticks);
		gd->xlbound = gd->xtickrange*floor(((double)xMin)/gd->xtickrange);
	}
	else {
		// x is constant
		log_debug("TODO: implement x constant logic\n");
	}

	if (yMin != yMax) {
		double range = yMax - yMin;
		gd->ytickrange = round_tr(range/numyticks);
		gd->ylbound = gd->ytickrange*floor(((double)yMin)/gd->ytickrange);
	}
	else {
		// y is constant
		log_debug("TODO: implement y constant logic\n");
	}
	return gd;
}

void destroy_GridData(GridData *gd) {
	free(gd);
}

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

void render_tick_number(SDL_Renderer *renderer, TTF_Font *font, int num, Point *tickpos, bool alongY) {
	SDL_SetRenderDrawColor(renderer, axisTextColor.r, axisTextColor.g, axisTextColor.b, axisTextColor.a);
	int textwidth=0, textheight=0;
	char *s = malloc(sizeof(char)*15);
	snprintf(s, 15, "%d", num);
	TTF_SizeText(font, s, &textwidth, &textheight);
	if (alongY) {
		SDL_RenderText(renderer, tickpos->x-textwidth-p_btl-4, round(tickpos->y-((double)textheight)/2),
					   font, s);
	}
	else {
		SDL_RenderText(renderer, round(tickpos->x-((double)textwidth)/2), tickpos->y+p_btl+4,
					   font, s);
	}
	free(s);
}

void render_plot(SDL_Renderer *renderer, GridData *gd) {
	// draw axes; note the subpixel correct rendering
	SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
	double xtickwidth = round((double)(p_brx-p_tlx)/gd->numxticks);
	double ytickwidth = round((double)(p_bry-p_tly)/gd->numyticks);
	// gridlines
	// notice cleverly placed +1's - SDL does not draw the last point in the line
	for (int i=1; i<gd->numyticks; i++) {
		int y = round(p_bry - ytickwidth*i -1);
		SDL_RenderDrawDashedLine(renderer, p_tlx, y, p_brx+1, y, 10, 5);
	}
	for (int i=1; i<gd->numxticks; i++) {
		int x = round(xtickwidth*i + p_tlx);
		SDL_RenderDrawDashedLine(renderer, x, p_tly, x, p_bry+1, 10, 5);
	}
	// axes
	SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	SDL_RenderDrawLine(renderer, p_tlx, p_tly, p_tlx, p_bry+1);
	SDL_RenderDrawLine(renderer, p_tlx, p_bry, p_brx+1, p_bry);
	// markings and text
	TTF_Font *opensans_12pt = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 12);
	for (int i=0; i<=gd->numxticks; i++) {
		if (i != gd->numxticks) {
			for (int j=1; j<5; j++) {
				int x = round(p_tlx+xtickwidth*(i+0.2*j));
				SDL_RenderDrawLine(renderer, x, p_bry, x, p_bry+p_stl);
			}
		}
		int x = round(p_tlx + xtickwidth*i);
		SDL_RenderDrawLine(renderer, x, p_bry, x, p_bry+p_btl);
		int num = gd->xlbound + i*gd->xtickrange;
		Point tickpos = {x, p_bry};
		render_tick_number(renderer, opensans_12pt, num, &tickpos, false);
		SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	}
	for (int i=0; i<=gd->numyticks; i++) {
		if (i != gd->numyticks) {
			for (int j=1; j<5; j++) {
				int y = round(p_bry-ytickwidth*(i+0.2*j));
				SDL_RenderDrawLine(renderer, p_tlx, y, p_tlx-p_stl, y);
			}
		}
		int y = round(p_bry-ytickwidth*i-1);
		SDL_RenderDrawLine(renderer, p_tlx, y, p_tlx-p_btl, y);
		SDL_SetRenderDrawColor(renderer, axisTextColor.r, axisTextColor.g, axisTextColor.b, axisTextColor.a);
		int num = gd->ylbound + i*gd->ytickrange;
		Point tickpos = {p_tlx, y};
		render_tick_number(renderer, opensans_12pt, num, &tickpos, true);
		SDL_SetRenderDrawColor(renderer, axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	}
	TTF_CloseFont(opensans_12pt);
	// x axis highlight
	SDL_SetRenderDrawColor(renderer, xAxisHighlightColor.r, xAxisHighlightColor.b, xAxisHighlightColor.g, xAxisHighlightColor.a);
	SDL_RenderDrawLine(renderer, p_tlx, p_bry-1, p_brx+1, p_bry-1);
}

void render_points(SDL_Renderer *renderer, DataSet *ds, GridData *gd, SDL_Color *color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	for (int i=0; i<ds->ptList->head; i++) {
		Point *p = ds->ptList->data[i];
		int px = p->x;
		int py = p->y;
		int x = p_tlx + round((double)(p_brx-p_tlx)*(px-gd->xlbound)/(gd->xtickrange*gd->numxticks));
		int y = p_bry - round((double)(p_bry-p_tly)*(py-gd->ylbound)/(gd->ytickrange*gd->numyticks));
		//log_debug("Point to plot for (%d,%d) is (%d,%d)\n",px,py,x,y);
		SDL_RenderFillCircle(renderer, x, y, 5);
	}
}

int k_tly = 0.9*HEIGHT;

typedef struct DataKey {
	SDL_Color *color;
	char *name;
} DataKey;

void render_keys(SDL_Renderer *renderer, int nkeys, DataKey **keys) {
	TTF_Font *opensans_16pt = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 16);
	int padding = 4;
	int k_width = 0;
	int *widths = malloc(sizeof(int)*nkeys);
	int height;
	int pw = 0;
	for (int i=0; i<nkeys; i++) {
		// measure up size of bounding box
		TTF_SizeText(opensans_16pt, keys[i]->name, &widths[i], &height);
		pw = k_width;
		k_width += (3*padding + 8 + widths[i]);
		widths[i] = pw;
	}
	int k_tlx = WIDTH/2 - k_width/2;
	for (int i=0; i<nkeys; i++) {
		int x = k_tlx + widths[i];
		SDL_SetRenderDrawColor(renderer, keys[i]->color->r, keys[i]->color->g, keys[i]->color->b, keys[i]->color->a);
		SDL_RenderFillCircle(renderer, x+4, k_tly+(height/2), 4);
		SDL_SetRenderDrawColor(renderer, axisTextColor.r, axisTextColor.g, axisTextColor.b, axisTextColor.a);
		SDL_RenderText(renderer, x+12, k_tly, opensans_16pt, keys[i]->name);
	}
	TTF_CloseFont(opensans_16pt);
}

int plot(DataSet *ds, char *title) {
	// Standard SDL Application structure
	if (init_graphics() == -1) return -1;
	SDL_Window *win = create_SDL_window(title, WIDTH, HEIGHT);
	if (win == NULL) return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
	const SDL_Rect screen = {0, 0, WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &screen);

	GridData *gd = new_GridData(XTICKS, YTICKS, 1, &ds);
	render_plot(renderer, gd);
	SDL_Color *plotColor = gen_random_color(0.5, 0.95, 0xCF);
	render_points(renderer, ds, gd, plotColor);
	DataKey *key = malloc(sizeof(DataKey));
	key->color = plotColor;
	key->name = ds->name;
	log_debug("Renderer Color is (%d, %d, %d, %d)\n", plotColor->r, plotColor->g, plotColor->b, plotColor->a);
	render_keys(renderer, 1, &key);
	free(plotColor);
	free(key);
	destroy_GridData(gd);
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
	if (init_graphics() == -1) return -1;
	SDL_Window *win = create_SDL_window(title, WIDTH, HEIGHT);
	if (win == NULL) return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
	const SDL_Rect screen = {0, 0, WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &screen);

	GridData *gd = new_GridData(XTICKS, YTICKS, nsets, sets);
	DataKey **keys = malloc(sizeof(DataKey*)*nsets);
	render_plot(renderer, gd);
	for (int i=0; i<nsets; i++) {
		SDL_Color *plotColor = gen_random_color(0.5, 0.95, 0xCF);
		keys[i] = malloc(sizeof(DataKey));
		keys[i]->color = plotColor;
		keys[i]->name = sets[i]->name;
		render_points(renderer, sets[i], gd, plotColor);
	}
	render_keys(renderer, nsets, keys);
	for (int i=0; i<nsets; i++) {
		free(keys[i]->color);
		free(keys[i]);
	}
	free(keys);
	destroy_GridData(gd);
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
