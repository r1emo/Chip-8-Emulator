#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

#include "headers/chip8.h"

typedef struct
{
  SDL_Window* window;
  SDL_Renderer* renderer;
} sdl_t;

typedef struct
{
  int x;
  int y;
  char* rom;
} config_t;

void get_config(config_t* config);
bool init_window(sdl_t* sdl, config_t* config);
void cleanup(sdl_t sdl);

int main()
{
  sdl_t sdl = {0};
  config_t config = {0};

  get_config(&config);

  // initialize sdl2
  if (init_window(&sdl, &config))
  {
    // initialize cpu
    chip8_t cpu = {0};
    initialize(&cpu);

    SDL_Delay(3000);
  }

  // TODO: Figure out how to limit code to 60 cycles a second

  cleanup(sdl);

  return 0;
}

void get_config(config_t* config)
{
  // TODO: Add console args
  config->x = 64;
  config->y = 32;
}

bool init_window(sdl_t* sdl, config_t* config)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
  {
    SDL_Log("error initializing sdl: %s", SDL_GetError());
    return false;
  }
  
  sdl->window = SDL_CreateWindow("Chip8 Emulator",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                config->x, config->y, -1);
  
  if (!sdl->window)
  {
    SDL_Log("error initializing window: %s", SDL_GetError());
    return false;
  }

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);

  if (!sdl->renderer)
  {
    SDL_Log("error initializing renderer: %s", SDL_GetError());
    return false;
  }

  return true;
}

void cleanup(sdl_t sdl)
{
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  SDL_Quit();
}