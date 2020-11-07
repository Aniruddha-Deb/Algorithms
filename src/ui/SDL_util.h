#ifndef _SDL_UTIL_H_
#define _SDL_UTIL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int init_graphics();
SDL_Window* create_SDL_window(char* title, int width, int height);

void SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int r);
void SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int r);

void SDL_RenderDrawDashedLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int dashlen, int blanklen);
void SDL_RenderDrawRoundRect(SDL_Renderer *renderer, const SDL_Rect *rect, const int r);
void SDL_RenderFillRoundRect(SDL_Renderer *renderer, const SDL_Rect *rect, const int r);

void SDL_RenderText(SDL_Renderer *renderer, int tlx, int tly, TTF_Font *font, const char* text);

#endif
