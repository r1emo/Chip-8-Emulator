#include <stdio.h>
#include <SDL.h>

#include "headers/chip8.h"

struct
{
  SDL_Window* window;
} sdl_t;

int main()
{
  printf("Hello world");

  // initialize cpu
  chip8_t cpu = {0};
  initialize(&cpu);

  // TODO: Figure out how to limit code to 60 cycles a second

  return 0;
}