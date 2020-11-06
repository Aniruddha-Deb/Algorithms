#include "SDL_util.h"

void circle_test(SDL_Renderer *renderer) {
	for (int i=15; i<=150; i+=15) {
		SDL_RenderFillCircle(renderer, 300, 200, i);
	}
}

void line_test(SDL_Renderer *renderer) {
	for (int i=5, j=5; i<570; i+=30) {
		SDL_RenderDrawDashedLine(renderer, i, j, i+30, j+i, 5, 5);
	}
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
