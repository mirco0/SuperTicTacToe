#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include <SDL2/SDL.h>

/* Given an index and a n matrix, it returns a rect as a cell in the matrix */
SDL_Rect nmat_to_normalized_rect(int ind, const SDL_Rect* base, int n);

#endif