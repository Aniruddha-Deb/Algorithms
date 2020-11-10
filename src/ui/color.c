#include "color.h"
#include "../util/intgen.h"
#include "../util/logger.h"
#include <math.h>

#include <SDL2/SDL.h>

typedef struct RGBColor {
	double r, g, b;
} RGBColor;

static SDL_Color* HSV_to_RGB(int h, double s, double v, int a) {
	double c = s*v;
	double hh = (double)(h%360)/60;
	double x = c*(1 - fabs(fmod(hh, 2) - 1));
	RGBColor color;
	
	if      (0 <= hh && hh <= 1) color = (RGBColor){c, x, 0};
	else if (1 <  hh && hh <= 2) color = (RGBColor){x, c, 0};
	else if (2 <  hh && hh <= 3) color = (RGBColor){0, c, x};
	else if (3 <  hh && hh <= 4) color = (RGBColor){0, x, c};
	else if (4 <  hh && hh <= 5) color = (RGBColor){x, 0, c};
	else if (5 <  hh && hh <= 6) color = (RGBColor){c, 0, x};

	double m = v - c;
	color = (RGBColor){color.r + m, color.g + m, color.b + m};
	// now convert double RGB to uint8_t RGB
	SDL_Color *intColor = malloc(sizeof(SDL_Color*));
	*intColor = (SDL_Color){round(color.r*255), round(color.g*255), round(color.b*255), a};
	return intColor;
}

int h = -1;

SDL_Color* gen_random_color(double s, double v, int a) {
	if (h == -1) 
		h = gen_int(0, 360);
	else
		h += 223; // ((golden ratio - 1) * 360);
	log_debug("Random int generated is %d\n", h);
	return HSV_to_RGB(h, s, v, a);
}
