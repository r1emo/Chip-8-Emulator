#include "headers/chip8.h"
#include <stdio.h>
#include <stdlib.h>

// credit Laurence Muller for fontset("https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/"")
unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void initialize(chip8_t* cpu)
{
  cpu->pc = 0x200;
  cpu->opcode = 0;
  cpu->iReg = 0;
  cpu->sp = 0;

  // clear display
  for (int ii = 0; ii < (64*32); ii++) // TODO: switch to memset
    cpu->gfx[ii] = 0;

  // clear registers v0-vF
  for (int ii = 0; ii < 16; ii++) // TODO: switch to memset
    cpu->vReg[ii] = 0;

  for (int ii = 0; ii < 4096; ii++) // TODO: switch to memset
    cpu->memory[ii] = 0;
  
  // load fontset
  for (int ii = 0; ii < 80; ii++)
    cpu->memory[ii] = chip8_fontset[ii];

  cpu->sound_timer = 0;
}

int loadGame(chip8_t* cpu, char* filename)
{
  // TODO: HANDLE ERRORS BETTER
  int ret = 0;

  FILE* rom = fopen(filename, "rb");

  if (rom)
  {
    // get file size
    if (fseek(rom, 0, SEEK_END) == 0)
    {
      long buffer_size = ftell(rom);
      char* buffer = (char*)malloc(sizeof(char) * (buffer_size));

      // go back to begining of file
      rewind(rom);

      // read rom
      size_t result = fread(buffer, sizeof(char), (size_t)buffer_size, rom);
      if (result != buffer_size)
      {
        ret = -3;
      }

      // move rom from buffer to memory
      for (int ii = 0; ii < buffer_size; ii++)
        cpu->memory[ii + 0x200] = buffer[ii];

      free(buffer);
      fclose(rom);
    }
    else
    {
      ret = -2;
    }
  }
  else
  {
    ret = -1;
  }

  return ret;
}