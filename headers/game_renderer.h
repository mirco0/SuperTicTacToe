#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <game_input.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>


void GR_draw_grid(SDL_Renderer* renderer, SDL_Rect* bounds,SDL_Color color,SDL_bool draw_edges);
void GR_init(SDL_Renderer* renderer);
void GR_coord_to_nmat(SDL_Point* coord, int n, SDL_Rect* bounds, int* dst_i, int* dst_j);
void GR_mat_to_coord(int i, int j, int n, SDL_Rect* bounds, SDL_Point* dst_coords);
void GR_draw_circle(SDL_Renderer* renderer, SDL_Point* pointer_pos);
void GR_init_render_input();

#endif 
