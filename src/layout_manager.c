#include <game_input.h>
#include <stdio.h>

SDL_Rect nmat_to_normalized_rect(int ind, const SDL_Rect* base, int n){
    float width = (float)base->w / n;
    float height = (float)base->h / n;

    SDL_Point pos = INPUT_index_nmatrix(ind,n);
    pos.x = width*pos.x + base->x;
    pos.y = height*pos.y + base->y;
    
    SDL_Rect fraction = {
        .x = pos.x,
        .y = pos.y,
        .w = width,
        .h = height
    };
    return fraction;
}


