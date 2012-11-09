#include <stdio.h>
#include "SDL.h"

int RUNNING = 1;
int SCREEN_LOCK = 0;
int PIXEL_OFFSET = 1;

int x = 320;
int y = 240;

void handle_events(SDL_Event *event) {
  if (event->type == SDL_QUIT) {
    printf("Goodbye, have fun without me, if you must.\n");
    RUNNING = 0;
  }
}

void pixel(Uint32 *buffer, int x, int y, Uint32 color) {
  //update our buffer location to the correct location
  buffer += y * PIXEL_OFFSET + x;
  //dereference and set location to our color value
  *buffer = color;
}

void draw(SDL_Surface *screen) {
  Uint32 color = SDL_MapRGB(screen->format, 255, 255, 255);

  if (SCREEN_LOCK) {
    if (SDL_LockSurface(screen) < 0) {
      return;
    }
  }

  pixel((Uint32 *)screen->pixels, x, y, color);

  //just do some simple line drawing
  x += 1;
  y += 1;
  if (x == 640) x = 0;
  if (y == 480) y = 0;

  if (SCREEN_LOCK) {
    SDL_UnlockSurface(screen);
  }
  SDL_Flip(screen);
}
 
int main(int argc, char *argv[]) {
  printf("Do you remember how to code in c?\n");

  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  //create screen
  SDL_Surface *screen;
  screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  if (screen == NULL) {
    fprintf(stderr, "Unable to set screen: %s\n", SDL_GetError());
    exit(1);
  }

  //update a few globals 
  SCREEN_LOCK = SDL_MUSTLOCK(screen);
  PIXEL_OFFSET = screen->pitch / 4;


  atexit(SDL_Quit);

  //Begin main loop
  SDL_Event event;
  while(RUNNING == 1) {
    //handle queued events
    while (SDL_PollEvent(&event)) {
      handle_events(&event);
    }
    draw(screen);

    //pause for station identification
    //SDL_Delay(16);
  }

  exit(0);
}
