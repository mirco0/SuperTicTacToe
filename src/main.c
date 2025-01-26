#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include<game_handler.h>
#include<game_renderer.h>

#define RANDOM_COLOR (SDL_Color){.r = rand()%256, .g=rand()%256, .b=rand()%256, .a=1};
#define gridSize 3

int main(int argc, char** argv){  
  GR_init_render_input();

  return 0;
}

