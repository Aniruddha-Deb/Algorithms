#include "SDL_util.h"
#include "plotter.h"
#include "../util/ds.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void circle_test(SDL_Renderer *renderer) {
	for (int i=15; i<=150; i+=15) {
		SDL_RenderFillCircle(renderer, 300, 200, i);
	}
}

void line_test(SDL_Renderer *renderer) {
	int r = 100;
	for (double i=0; i<360; i+=9) {
		// draw i degree line
		printf("Drawing %d degree line\n", (int)i);
		SDL_RenderDrawDashedLine(renderer, 300, 200, (int)(300+r*cos(M_PI*i/180)), 
			(int)(200+r*sin(M_PI*i/180)), 10, 5);
	}
}

int main(int argc, char **argv) {
	DataSet *ds = new_DataSet("Test");
	DataSet_add(ds, new_Point(52, 56));
	DataSet_add(ds, new_Point(33, 21));
	DataSet_add(ds, new_Point(42, 66));
	plot(ds, "Title here");
}
