#include <SDL2/SDL_rect.h>
#include <game_input.h>
#include <stdio.h>

SDL_Point INPUT_index_nmatrix(int ind, int n){
  SDL_Point grid_pos;
  grid_pos.x = ind%n;
  grid_pos.y = ind/n;
  return grid_pos;
}

int INPUT_nmatrix_index(int x, int y, int n){
  return y*n+x;
}

void INPUT_coord_to_nmat(const SDL_Point* coord, int n, const SDL_Rect* bounds, int* dst_x, int* dst_y){
  int x = coord->x - bounds->x;
  int y = coord->y - bounds->y;
  *dst_x = (float)n / bounds->w*x;
  *dst_y = (float)n / bounds->h*y;
}

int INPUT_rawmouse_to_game(const SDL_Point* pointer_pos, const SDL_Rect* bounds, const SDL_Rect* smallbounds, int n, int* dst_index, int* dst_sub_index){
  if(!SDL_PointInRect(pointer_pos,bounds)){
    *dst_index = -1;
    *dst_sub_index = -1; 
    return 0;
  }
  int x, y;
  INPUT_coord_to_nmat(pointer_pos, n, bounds, &x, &y);
  *dst_index = INPUT_nmatrix_index(x,y,n);
	SDL_Rect offset = *smallbounds;
  offset.x += offset.w * x + bounds->x;
  offset.y += offset.h * y + bounds->y;
  INPUT_coord_to_nmat(pointer_pos, n, &offset, &x, &y);
  *dst_sub_index = INPUT_nmatrix_index(x,y,n);
  return 1;
}