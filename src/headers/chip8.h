#ifndef CHIP8_H
#define CHIP8_H

#include "opcode.h"

int VIDEO_WIDTH = 64;
int VIDEO_HEIGHT = 32;

typedef struct
{
  // current opcode
  unsigned short opcode;

  unsigned char memory[4096];

  // registers
  unsigned char vReg[16];
  unsigned short iReg;

  // program counter
  unsigned short pc;

  // graphics shiz
  unsigned char gfx[64 * 32];
  unsigned char drawFlag;

  // timers
  unsigned char delay_timer;
  unsigned char sound_timer;

  // stack shiz
  unsigned short stack[16];
  unsigned short sp;

  // user input stuff
  unsigned char keypad[16];
} chip8_t;

// util functions
void initialize(chip8_t* cpu);
int loadGame(chip8_t* cpu, char* filename);

#endif