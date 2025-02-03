#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <game_input.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>


void GR_draw_grid(SDL_Renderer* renderer,const SDL_Rect* bounds,SDL_Color color,SDL_bool draw_edges);
void GR_init(SDL_Renderer* renderer);
void GR_draw_game_state(SDL_Renderer* renderer, int GAME_STATE[9][10]);
void GR_draw_circle(SDL_Renderer* renderer,int turn, int index, int sub_index);
void GR_init_render_input();
void GR_draw_overlays(SDL_Renderer* renderer, SDL_Rect pos[9]);

#endif 
