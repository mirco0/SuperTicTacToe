#include <SDL2/SDL_rect.h>
#include <game_input.h>

SDL_Point INPUT_index_nmatrix(int ind, int n){
  SDL_Point grid_pos;
  grid_pos.x = ind/n;
  grid_pos.y = ind%n;
  return grid_pos;
}

int INPUT_nmatrix_index(int x, int y,int n){
  return x*n+y;
}

int clamp(int* c, int min, int max){
	if(*c < min){
		*c = min;
		return 1;
	}
	if(*c > max){
		*c = max;
		return 1;
	}
	return 0;
}


void GR_mat_to_coord(int i, int j, int n, SDL_Rect* bounds, SDL_Point* dst_coords){
  dst_coords->x = bounds->x + (float)bounds->w / n * i;
  dst_coords->y = bounds->y + (float)bounds->h / n * j;
}

void GR_coord_to_nmat(SDL_Point* coord, int n, SDL_Rect* bounds, int* dst_i, int* dst_j){
  int x = coord->x - bounds->x;
  int y = coord->y - bounds->y;
  *dst_i = (float)n / bounds->w*x;
  *dst_j = (float)n / bounds->h*y;
	clamp(dst_i,0, n);
	clamp(dst_j,0, n);
  //TODO: CLAMP 0,n
}

void INPUT_rawmouse_to_game(SDL_Point* pointer_pos, SDL_Rect* bounds, SDL_Rect* smallbounds, int* index, int* sub_index){
	int a, b;
  GR_coord_to_nmat(pointer_pos, 3, bounds, &a, &b);
	*index = INPUT_nmatrix_index(b, a, 3);
	
	smallbounds->x = bounds->x + smallbounds->w*a;
	smallbounds->y = bounds->y + smallbounds->h*b;
	
  GR_coord_to_nmat(pointer_pos, 3, smallbounds, &a, &b);
	*sub_index = INPUT_nmatrix_index(b, a, 3);
	
}

// SDL_Point INPUT_mouse_pos_to_grid(SDL_Point* mouse_pos,SDL_Rect* bounds){
//   int mat_x = 9./bounds->w * mouse_pos->x - (bounds->x);
//   int mat_y = 9./bounds->h * mouse_pos->y - (bounds->y);
//   return (SDL_Point){.x = mat_x, .y = mat_y};

// }