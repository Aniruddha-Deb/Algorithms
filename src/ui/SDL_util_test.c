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

void plotter_test() {
	DataSet *ds = new_DataSet("Test");
	DataSet_add(ds, new_Point(50, 80287));
	DataSet_add(ds, new_Point(100, 308221));
	DataSet_add(ds, new_Point(150, 509354));
	DataSet_add(ds, new_Point(200, 893770));
	DataSet_add(ds, new_Point(300, 837872));
	DataSet_add(ds, new_Point(500, 389363));
	DataSet_add(ds, new_Point(700, 300789));
	DataSet_add(ds, new_Point(750, 371039));
	DataSet_add(ds, new_Point(800, 411376));
	DataSet_add(ds, new_Point(850, 472281));
	DataSet_add(ds, new_Point(900, 384738));
	DataSet_add(ds, new_Point(950, 362343));
	DataSet_add(ds, new_Point(1000, 389826));
	DataSet_add(ds, new_Point(1050, 553622));
	DataSet_add(ds, new_Point(1100, 495191));
	DataSet_add(ds, new_Point(1150, 666203));
	DataSet_add(ds, new_Point(1200, 555769));
	DataSet_add(ds, new_Point(1250, 586373));
	DataSet_add(ds, new_Point(1300, 648324));
	DataSet_add(ds, new_Point(1350, 783533));
	DataSet_add(ds, new_Point(1400, 763920));
	DataSet_add(ds, new_Point(1450, 848476));
	DataSet_add(ds, new_Point(1500, 859247));
	DataSet_add(ds, new_Point(1600, 966006));
	DataSet_add(ds, new_Point(1650, 1043372));
	DataSet_add(ds, new_Point(1700, 2164402));
	DataSet_add(ds, new_Point(1750, 1985752));
	DataSet_add(ds, new_Point(1800, 1863389));
	DataSet_add(ds, new_Point(1850, 2232379));
	DataSet_add(ds, new_Point(1900, 2166679));
	DataSet_add(ds, new_Point(1950, 2224148));
	DataSet_add(ds, new_Point(2000, 2516448));
	DataSet_add(ds, new_Point(2050, 1591062));
	DataSet_add(ds, new_Point(2100, 1625197));
	DataSet_add(ds, new_Point(2150, 1709959));
	DataSet_add(ds, new_Point(2200, 2814147));
	DataSet_add(ds, new_Point(2250, 1862227));
	DataSet_add(ds, new_Point(2300, 3130461));
	DataSet_add(ds, new_Point(2350, 2166300));
	DataSet_add(ds, new_Point(2400, 3612858));
	DataSet_add(ds, new_Point(2450, 2464370));
	DataSet_add(ds, new_Point(2500, 2380222));
	DataSet_add(ds, new_Point(2550, 2835326));
	DataSet_add(ds, new_Point(2600, 3066908));
	DataSet_add(ds, new_Point(2650, 2752560));
	DataSet_add(ds, new_Point(2700, 3052529));
	DataSet_add(ds, new_Point(2750, 3004961));
	DataSet_add(ds, new_Point(2800, 3892322));
	DataSet_add(ds, new_Point(2850, 3467304));
	DataSet_add(ds, new_Point(2900, 3997560));
	DataSet_add(ds, new_Point(2950, 3618997));
	DataSet_add(ds, new_Point(3000, 3222413));
	DataSet_add(ds, new_Point(3050, 3969928));
	DataSet_add(ds, new_Point(3100, 3821322));
	DataSet_add(ds, new_Point(3150, 4085457));
	DataSet_add(ds, new_Point(3200, 4340036));
	DataSet_add(ds, new_Point(3250, 5095220));
	DataSet_add(ds, new_Point(3300, 4414881));
	DataSet_add(ds, new_Point(3350, 4126514));
	DataSet_add(ds, new_Point(3400, 4278274));
	DataSet_add(ds, new_Point(3450, 5207445));
	DataSet_add(ds, new_Point(3500, 4814505));
	DataSet_add(ds, new_Point(3550, 4596505));
	DataSet_add(ds, new_Point(3600, 4684067));
	DataSet_add(ds, new_Point(3650, 4863973));
	DataSet_add(ds, new_Point(3700, 4968991));
	DataSet_add(ds, new_Point(3750, 5929612));
	DataSet_add(ds, new_Point(3800, 5978380));
	DataSet_add(ds, new_Point(3850, 5634186));
	DataSet_add(ds, new_Point(3900, 5873852));
	DataSet_add(ds, new_Point(3950, 6100325));
	DataSet_add(ds, new_Point(4000, 6220298));
	DataSet_add(ds, new_Point(4050, 6117306));
	DataSet_add(ds, new_Point(4100, 5935654));
	DataSet_add(ds, new_Point(4150, 6947061));
	DataSet_add(ds, new_Point(4200, 6722976));
	DataSet_add(ds, new_Point(4250, 6568891));
	DataSet_add(ds, new_Point(4300, 6712233));
	DataSet_add(ds, new_Point(4350, 6954006));
	DataSet_add(ds, new_Point(4400, 7084017));
	DataSet_add(ds, new_Point(4450, 7627578));
	DataSet_add(ds, new_Point(4500, 7559646));
	DataSet_add(ds, new_Point(4550, 7608039));
	DataSet_add(ds, new_Point(4600, 9706385));
	DataSet_add(ds, new_Point(4650, 9627216));
	DataSet_add(ds, new_Point(4700, 8142935));
	DataSet_add(ds, new_Point(4750, 8166052));
	DataSet_add(ds, new_Point(4800, 8283684));
	DataSet_add(ds, new_Point(4850, 9571634));
	DataSet_add(ds, new_Point(4950, 9187290));
	DataSet_add(ds, new_Point(5000, 9615109));
	plot(ds, "Scatter Chart Example");
	destroy_DataSet(ds);
}

int main(int argc, char **argv) {
	if (init_graphics() == -1) return -1;
	SDL_Window *win = create_SDL_window("Bresenham Circle Test", 600, 400);
	if (win == NULL) return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	const SDL_Rect screen = {0, 0, 600, 400};
	SDL_RenderFillRect(renderer, &screen);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	line_test(renderer);

	SDL_RenderPresent(renderer);

	SDL_Event e;
	int quit = 1;
	while (quit != 0) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = 0;
				break;
			}
		}
	}
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

