#ifndef GAME_INPUT
#define GAME_INPUT

#include <SDL2/SDL_rect.h>

// Gives the indexes of a [N][N] grid given an index of a [2N] array 
SDL_Point INPUT_index_nmatrix(int ind, int n);
// Gives the index of a [2N] array given the indexes of a [N][N] grid  
int INPUT_nmatrix_index(int x, int y, int n);
// Gives the indexes of the GAME given the pointer position and the two grids bounds  
int INPUT_rawmouse_to_game(const SDL_Point* pointer_pos, const SDL_Rect* bounds, const SDL_Rect* smallbounds, int n, int* dst_index, int* dst_sub_index);

#endif
