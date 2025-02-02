#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <game_renderer.h>
#include <game_handler.h>
#include <layout_manager.h>

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

#define GRID_W 400
#define GRID_H 400

const SDL_Rect grid_bounds = {.x=100, .y=0, .w = GRID_W, .h = GRID_H};
const SDL_Rect smallgrid_bounds = {.x=0, .y=0, .w = (float)GRID_W/GRID_SIZE+1, .h = (float)GRID_H/GRID_SIZE+1};


SDL_Rect* pos;
SDL_Texture* texture;
SDL_Texture* closed_texture;
SDL_Texture* circle_texture;
SDL_Texture* cross_texture;

int index_, sub_index_;

SDL_Window* window;
SDL_Renderer* renderer;


void GR_draw_grid(SDL_Renderer* renderer,const SDL_Rect* bounds, SDL_Color color, SDL_bool draw_edges){
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
  closed_texture = IMG_LoadTexture(renderer, "assets/closed.png");
  circle_texture = IMG_LoadTexture(renderer, "assets/circle.png");
  cross_texture = IMG_LoadTexture(renderer, "assets/cross.png");
  pos = malloc(sizeof(SDL_Rect));

  //TODO: FIX HARDCODED
  pos->w = 45; //400 / 9
  pos->h = 45;
}

void GR_draw_circle(SDL_Renderer* renderer, int turn, int index, int sub_index){
  if(index == -1|| sub_index == -1) return;
  SDL_Rect big_o = nmat_to_normalized_rect(index, &grid_bounds, 3);
  SDL_Rect small_o = nmat_to_normalized_rect(sub_index, &smallgrid_bounds, 3);
  small_o.x += big_o.x;
  small_o.y += big_o.y;
  SDL_Texture *player_texture = turn? cross_texture:circle_texture;
  SDL_SetTextureAlphaMod(player_texture,100);
  SDL_RenderCopy(renderer, player_texture, NULL,&small_o);
  SDL_SetTextureAlphaMod(player_texture,255);

}

void GR_draw_frame(const SDL_Point* pointer_pos){
  SDL_Rect draw = smallgrid_bounds;
  SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
  SDL_RenderClear(renderer);

  //// GRID
  for(int y = 0; y<3; y++){
    for(int x = 0; x<3; x++){
      draw.x = grid_bounds.w / 3 * x + grid_bounds.x;
      draw.y = grid_bounds.h / 3 * y + grid_bounds.y;
      SDL_Color B = BLUE;
      GR_draw_grid(renderer,&draw,B,0);
    }
  }

  GR_draw_grid(renderer,&grid_bounds,RED,1);
  
    //TODO: REMOVE
  // for(int i = 0; i<9; i++){
  //   rects[i] = nmat_to_normalized_rect(i,&grid_bounds,3);
  // }
  
  // int index,sub_index;
  int in_grid = INPUT_rawmouse_to_game(pointer_pos, &grid_bounds, &smallgrid_bounds,3,&index_,&sub_index_);
  int GAME_STATE[9][10];
  get_GAME_STATE(GAME_STATE);
  int valid_move = GAME_validate_move(index_,sub_index_);
  GR_draw_game_state(renderer,GAME_STATE);
  if(valid_move)
    GR_draw_circle(renderer,GAME_get_turn(),index_,sub_index_);
  // rects[2].w = 0;
  // GR_draw_overlays(renderer,rects);
          
}

void GR_draw_game_state(SDL_Renderer* renderer, int GAME_STATE[9][10]){
  for(int i = 0; i<9; i++){
    SDL_Point xy = INPUT_index_nmatrix(i, 3);
    for(int j = 0; j<9; j++){
      if(GAME_STATE[i][j] == -1) continue;
      SDL_Rect draw = nmat_to_normalized_rect(j, &smallgrid_bounds, 3);
      draw.x += grid_bounds.x + smallgrid_bounds.w * xy.x;
      draw.y += grid_bounds.y + smallgrid_bounds.h * xy.y;
      SDL_Texture* piece_texture = GAME_STATE[i][j] == 0? circle_texture: cross_texture;
      SDL_RenderCopy(renderer, piece_texture,NULL,&draw);
    }

  }

  for(int i = 0; i<9; i++){
    if(GAME_STATE[i][9] == -1) continue;
    SDL_Rect draw = nmat_to_normalized_rect(i, &grid_bounds, 3);
    SDL_RenderCopy(renderer, texture,NULL,&draw);
    SDL_Texture* piece_texture = GAME_STATE[i][9] == 0? circle_texture: cross_texture;
    SDL_RenderCopy(renderer, piece_texture,NULL,&draw);
  }
}

void GR_draw_overlays(SDL_Renderer* renderer, SDL_Rect pos[9]){
  for(int i = 0; i<9; i++){
    SDL_RenderCopy(renderer,closed_texture,0,&pos[i]);
  }
}

void GR_init_render_input(){
  SDL_Rect rects[9];
  int quit = 0;

  window = SDL_CreateWindow("",0,0,600,400,0);
  renderer = SDL_CreateRenderer(window,0,0);
  
  GR_init(renderer);
  GAME_init();

  SDL_Event event;
  SDL_Point pointer_pos = {.x = 0, .y = 0};

  while(!quit){
    while(SDL_WaitEvent(&event)){
      switch (event.type) {
        case SDL_QUIT:
          quit = 1;
          exit(0);
          break;

        case SDL_MOUSEMOTION:
          SDL_GetMouseState(&pointer_pos.x, &pointer_pos.y);
          GR_draw_frame(&pointer_pos);
          break;
        
        case SDL_MOUSEBUTTONDOWN:
          GAME_play_move(index_,sub_index_);
          GR_draw_frame(&pointer_pos);
          break;
      }
      SDL_RenderPresent(renderer);
    }
  }
}