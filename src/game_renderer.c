#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <game_renderer.h>

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#include "game_input.h"
#include "game_handler.h"


#define RED (SDL_Color){.r = 255, .g = 0, .b = 0,.a = 1}
#define BLUE (SDL_Color){.r = 0, .g = 0, .b = 255,.a = 1}

#define GRID_SIZE 3
#define SUBGRID_SIZE 3

//TODO: FIX HARDCODED
SDL_Rect grid_bounds = {.x=100, .y=0, .w = 400, .h = 400};
SDL_Rect smallgrid_bounds = {.x=0, .y=0, .w = 133, .h = 133};


SDL_Rect* pos;
SDL_Texture* texture;


SDL_Window* window;
SDL_Renderer* renderer;


void GR_draw_grid(SDL_Renderer* renderer,SDL_Rect* bounds, SDL_Color color, SDL_bool draw_edges){
  SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
  for(int i = !draw_edges; i<GRID_SIZE+draw_edges; i++){
    int pos_x = bounds->w / GRID_SIZE * i;
    SDL_RenderDrawLine(renderer, bounds->x + pos_x, bounds->y, bounds->x + pos_x, bounds->y + bounds->h);
  }

  for(int i = !draw_edges; i<GRID_SIZE+draw_edges; i++){
    int pos_y = bounds->h / GRID_SIZE * i;
    SDL_RenderDrawLine(renderer, bounds->x, bounds->y + pos_y, bounds->x + bounds->w, bounds->y + pos_y);
  }

  SDL_SetRenderDrawColor(renderer,255,255,255,1);
}

void GR_init(SDL_Renderer* renderer){
  texture = IMG_LoadTexture(renderer, "assets/grid_hover.png");
  pos = malloc(sizeof(SDL_Rect));

  //TODO: FIX HARDCODED
  pos->w = 45;
  pos->h = 45;
}


//TODO: SEPARATE game_input calls from actual render 
void GR_draw_circle(SDL_Renderer* renderer, SDL_Point* pointer_pos){
  SDL_Point m;
  int a, b;
  
  GR_coord_to_nmat(pointer_pos, 3, &grid_bounds, &a, &b);
	
	smallgrid_bounds.x = grid_bounds.x + smallgrid_bounds.w*a;
	smallgrid_bounds.y = grid_bounds.y + smallgrid_bounds.h*b;
	
  GR_coord_to_nmat(pointer_pos, 3, &smallgrid_bounds, &a, &b);
	

  GR_mat_to_coord(a, b, 3, &smallgrid_bounds,&m);
	pos->x = m.x;
	pos->y = m.y;
	
  SDL_RenderCopy(renderer,texture,0,pos);


  //TODO: FIX HARDCODED 400 / 3
	SDL_Rect B = {.h = 133, .w = 133};
	
  SDL_Point C;
	GR_mat_to_coord(a, b, 3, &grid_bounds,&C);
	B.x = C.x;
	B.y = C.y;
	SDL_RenderCopy(renderer,texture,0,&B);


}

void GR_draw_frame(){
  SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
  SDL_RenderClear(renderer);

  //// GRID
  for(int y = 0; y<3; y++){
    for(int x = 0; x<3; x++){
      smallgrid_bounds.x = 400 / 3 * x + grid_bounds.x;
      smallgrid_bounds.y = 400 / 3 * y + grid_bounds.y;
      SDL_Color B = BLUE;
      GR_draw_grid(renderer,&smallgrid_bounds,B,0);
    }
  }

  GR_draw_grid(renderer,&grid_bounds,RED,1);
  
}

void GR_init_render_input(){
  int quit = 0;

  window = SDL_CreateWindow("",0,0,600,400,0);
  renderer = SDL_CreateRenderer(window,0,0);
  
  GR_init(renderer);

  SDL_Event event;
  SDL_Point pointer_pos = {.x = 0, .y = 0};
  
  int moveA = 0, moveB = 0;

  while(!quit){
    while(SDL_WaitEvent(&event)){
      switch (event.type) {
        case SDL_QUIT:
          quit = 1;
          exit(0);
          break;

        case SDL_MOUSEMOTION:
          SDL_GetMouseState(&pointer_pos.x, &pointer_pos.y);
          GR_draw_frame();
          INPUT_rawmouse_to_game(&pointer_pos, &grid_bounds, &smallgrid_bounds,&moveA,&moveB);
          GR_draw_circle(renderer,&pointer_pos);
          break;
        
        case SDL_MOUSEBUTTONDOWN:
          GAME_play_move(moveA,moveB,0);
          break;
      }
      SDL_RenderPresent(renderer);
    }
  }
}