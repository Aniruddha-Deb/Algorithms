#include "SDL_util.h"
#include "../util/gen.h"

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_log.h>

int init_graphics() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL TTF: %s\n", TTF_GetError());
		return -1;
	}
	return 1;
}

SDL_Window* create_SDL_window(char *title, int width, int height) {
	SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
					 width, height, SDL_WINDOW_OPENGL);
	if (win == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Could not create Window: %s\n", SDL_GetError());
	}
	return win;
}

static void render_circ_pts(SDL_Renderer *renderer, int x0, int y0, int x, int y) {
	SDL_RenderDrawPoint(renderer, x0+x, y0+y);
	SDL_RenderDrawPoint(renderer, x0-x, y0+y);
	SDL_RenderDrawPoint(renderer, x0+x, y0-y);
	SDL_RenderDrawPoint(renderer, x0-x, y0-y);
	SDL_RenderDrawPoint(renderer, x0+y, y0+x);
	SDL_RenderDrawPoint(renderer, x0-y, y0+x);
	SDL_RenderDrawPoint(renderer, x0+y, y0-x);
	SDL_RenderDrawPoint(renderer, x0-y, y0-x);
}

static void render_circ_lines(SDL_Renderer *renderer, int x0, int y0, int x, int y, bool xch) {
	// renders every point only once, so rendering with alpha < 0xFF is not an 
	// issue. Hell yeah!!!
	SDL_RenderDrawLine(renderer, x0-x, y0-y, x0+x+1, y0-y);
	if (y != 0) {
		SDL_RenderDrawLine(renderer, x0-x, y0+y, x0+x+1, y0+y);
	}
	if (xch && x != y) {
		SDL_RenderDrawLine(renderer, x0-y, y0-x, x0+y+1, y0-x);
		SDL_RenderDrawLine(renderer, x0-y, y0+x, x0+y+1, y0+x);
	}
}

// Bresenham circle drawing algorithm
static void render_circle(SDL_Renderer *renderer, int cx, int cy, int r, bool fill) {
	int x = r;
	int y = 0;
	int dx = 1-2*r;
	int dy = 1;
	int re = 0;
	bool xch = true;
	while (x >= y) {
		if (fill) render_circ_lines(renderer, cx, cy, x, y, xch);
		else render_circ_pts(renderer, cx, cy, x, y);
		xch = false;
		y++;
		re += dy;
		dy += 2;
		if (2*re + dx > 0) {
			xch = true;
			x--;
			re += dx;
			dx += 2;
		}
	}
}

void SDL_RenderDrawCircle(SDL_Renderer *renderer, int cx, int cy, int r) {
	render_circle(renderer, cx, cy, r, false);
}

void SDL_RenderFillCircle(SDL_Renderer *renderer, int cx, int cy, int r) {
	render_circle(renderer, cx, cy, r, true);
}

// Bresenham line algorithm
// similar to SDL_RenderDrawLine: draws x0, y0 and does not draw x1, y1 (x0 <= L < x1)
void SDL_RenderDrawDashedLine(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int dashlen, int blanklen) {
	int Dx = x1 - x0;
	int Dy = y1 - y0;
	// dirx, diry - direction of line
	// the direction being iterated over is 1 or -1, and the other one is 0
	int dirx = 0, diry = 0;
	// incx, incy - increment of line
	// the direction being iterated over is set to the same as dirx, while 
	// the other one is 1, -1 or 0 depending on line direction.
	int incx = 0, incy = 0;

	// first find the variable we will be iterating over - X or Y
	int longest = abs(Dx);
	int shortest = abs(Dy);
	if (longest < shortest) {
		// We'll iterate over y, so swap longest and shortest and then set dir* 
		// and inc* appropriately
		swap(&longest, &shortest);
		dirx = 0;
		if (Dx < 0) incx = -1; else if (Dx > 0) incx = 1;
		if (Dy < 0) diry = -1; else diry = 1;
		incy = diry;
	}
	else {
		// Iterating over x
		diry = 0;
		if (Dy < 0) incy = -1; else if (Dy > 0) incy = 1;
		if (Dx < 0) dirx = -1; else dirx = 1;
		incx = dirx;
	}

	int err = 0;
	int x = x0;
	int y = y0;
	for (int i=0; i<longest; i++) {
		if (i%(dashlen+blanklen) < dashlen)
			SDL_RenderDrawPoint(renderer, x, y);
		err += shortest;
		if (2*(err+shortest) < longest) {
			x += dirx;
			y += diry;
		}
		else {
			err -= longest;
			x += incx;
			y += incy;
		}
	}
}

void SDL_RenderText(SDL_Renderer *renderer, int tlx, int tly, TTF_Font *font, const char* text) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	SDL_Color color = {r, g, b, a};
	SDL_Surface *surf = TTF_RenderText_Blended(font, text, color);
	SDL_Rect textLoc = {tlx, tly, surf->w, surf->h};
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_RenderCopy(renderer, texture, NULL, &textLoc);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}
