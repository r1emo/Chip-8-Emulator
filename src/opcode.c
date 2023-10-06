#include "headers/opcode.h"

void CLS(chip8_t* cpu)
{
  // clear display
  for (int ii = 0; ii < (64*32); ii++)
    cpu->gfx[ii] = 0;
  cpu->pc += 2;
}

void RET(chip8_t* cpu)
{
  cpu->pc = cpu->stack[cpu->sp];
  cpu->sp -= 1;
}

void SYSaddr(chip8_t* cpu)
{
  cpu->pc = cpu->opcode & 0x0FFF;
}

void JPaddr(chip8_t* cpu)
{
  cpu->pc = cpu->opcode & 0x0FFF;
}

void CALLaddr(chip8_t* cpu)
{
  cpu->sp += 1;
  cpu->stack[cpu->sp] = cpu->pc;
  cpu->pc = cpu->opcode & 0x0FFF;
}

void SEVxByte(chip8_t* cpu)
{
  int reg = (cpu->opcode & 0x0F00) >> 8;
  if (cpu->vReg[reg] == (cpu->opcode & 0x00FF))
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void SNEVxByte(chip8_t* cpu)
{
  int reg = (cpu->opcode & 0x0F00) >> 8;
  if (cpu->vReg[reg] != (cpu->opcode & 0x00FF))
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void SEVxVy(chip8_t* cpu)
{
  int regx = (cpu->opcode & 0x0F00) >> 8;
  int regy = (cpu->opcode & 0x00F0) >> 4;
  if (cpu->vReg[regx] == cpu->vReg[regy])
  {
    cpu->pc += 4;
  }
  else
    cpu->pc += 2;
}

void LDVxByte(chip8_t* cpu)
{
  cpu->vReg[(cpu->opcode & 0x0F00) >> 8] = cpu->opcode & 0x00FF;
  cpu->pc += 2;
}

void ADDVxByte(chip8_t* cpu)
{
  int reg = (cpu->opcode * 0x0F00) >> 8;
  if (cpu->vReg[reg] > (0xFF - (cpu->opcode & 0x00FF)))
    cpu->vReg[0xF] = 1;
  else
    cpu->vReg[0xF] = 0;
  
  cpu->vReg[reg] += (cpu->opcode & 0x00FF);
  cpu->pc += 2;
}

void LDVxVy(chip8_t* cpu)
{
  int regx = (cpu->opcode & 0x0F00) >> 8;
  int regy = (cpu->opcode & 0x00F0) >> 4;

  cpu->vReg[regx] = cpu->vReg[regy];

  cpu->pc += 2;
}