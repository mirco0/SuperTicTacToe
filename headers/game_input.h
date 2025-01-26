#ifndef GAME_INPUT
#define GAME_INPUT

#include <SDL2/SDL_rect.h>

SDL_Point INPUT_index_nmatrix(int ind, int n);
int INPUT_nmatrix_index(int x, int y, int n);
SDL_Point INPUT_mouse_pos_to_grid(SDL_Point* mouse_pos,SDL_Rect* bounds);
void INPUT_rawmouse_to_game(SDL_Point* pointer_pos, SDL_Rect* bounds, SDL_Rect* smallbounds, int* index, int* sub_index);

#endif
