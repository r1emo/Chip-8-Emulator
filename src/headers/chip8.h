#ifndef CHIP8_H
#define CHIP8_H

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
  unsigned char key[16];
} chip8_t;

// util functions
void initialize(chip8_t* cpu);
int loadGame(chip8_t* cpu, char* filename);

// op code functions
void CLS(chip8_t* cpu);
void RET(chip8_t* cpu);
void SYSaddr(chip8_t* cpu);
void JPaddr(chip8_t* cpu);
void CALLaddr(chip8_t* cpu);
void SEVxByte(chip8_t* cpu);
void SNEVxByte(chip8_t* cpu);
void SEVxVy(chip8_t* cpu);
void LDVxByte(chip8_t* cpu);
void ADDVxByte(chip8_t* cpu);
void LDVxVy(chip8_t* cpu);

#endif