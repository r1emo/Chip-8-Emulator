#include "headers/opcode.h"
#include <time.h>

void CLS(chip8_t* cpu)
{
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
  unsigned short reg = (cpu->opcode & 0x0F00) >> 8;
  if (cpu->vReg[reg] == (cpu->opcode & 0x00FF))
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void SNEVxByte(chip8_t* cpu)
{
  unsigned short reg = (cpu->opcode & 0x0F00) >> 8;
  if (cpu->vReg[reg] != (cpu->opcode & 0x00FF))
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void SEVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;
  if (cpu->vReg[regx] == cpu->vReg[regy])
    cpu->pc += 4;
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
  unsigned short reg = (cpu->opcode * 0x0F00) >> 8;
  if (cpu->vReg[reg] > (0xFF - (cpu->opcode & 0x00FF)))
    cpu->vReg[0xF] = 1;
  else
    cpu->vReg[0xF] = 0;
  
  cpu->vReg[reg] += (cpu->opcode & 0x00FF);
  cpu->pc += 2;
}

void LDVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  cpu->vReg[regx] = cpu->vReg[regy];

  cpu->pc += 2;
}

void ORVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  cpu->vReg[regx] = (cpu->vReg[regx] | cpu->vReg[regy]);

  cpu->pc += 2;
}

void ANDVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  cpu->vReg[regx] = (cpu->vReg[regx] & cpu->vReg[regy]);

  cpu->pc += 2;
}

void XORVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  cpu->vReg[regx] = (cpu->vReg[regx] ^ cpu->vReg[regy]);

  cpu->pc += 2;
}

void ADDVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  if (cpu->vReg[regx] > (0xFF - cpu->vReg[regy]))
    cpu->vReg[0xF] = 1;
  else
    cpu->vReg[0xF] = 0;

  cpu->vReg[regx] = cpu->vReg[regx] + cpu->vReg[regy];

  cpu->pc += 2;
}

void SUBVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  // for some reason VF is handled in reverse here from the adds, don't question it
  if (cpu->vReg[regx] > cpu->vReg[regy])
    cpu->vReg[0xF] = 1; // no underflow
  else
    cpu->vReg[0xF] = 0; // underflow

  cpu->vReg[regx] = cpu->vReg[regx] - cpu->vReg[regy];

  cpu->pc += 2;
}

void SHRVx(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;

  if ((cpu->vReg[regx] & 1))
    cpu->vReg[0xF] = 1;
  else
    cpu->vReg[0xF] = 0;
  
  cpu->vReg[regx] = cpu->vReg[regx] >> 1;

  cpu->pc += 2;
}

void SUBNVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  // for some reason VF is handled in reverse here from the adds, don't question it
  if (cpu->vReg[regy] > cpu->vReg[regx])
    cpu->vReg[0xF] = 1; // no underflow
  else
    cpu->vReg[0xF] = 0; // underflow

  cpu->vReg[regx] = cpu->vReg[regy] - cpu->vReg[regx];

  cpu->pc += 2;
}

void SHLVx(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;

  if ((cpu->vReg[regx] & 0x80))
    cpu->vReg[0xF] = 1;
  else
    cpu->vReg[0xF] = 0;
  
  cpu->vReg[regx] = cpu->vReg[regx] << 1;

  cpu->pc += 2;
}

void SNEVxVy(chip8_t* cpu)
{
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  unsigned short regy = (cpu->opcode & 0x00F0) >> 4;

  if (cpu->vReg[regx] != cpu->vReg[regy])
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void LDI(chip8_t* cpu)
{
  cpu->iReg = (cpu->opcode & 0x0FFF);
  cpu->pc += 2;
}

void JPV0(chip8_t* cpu)
{
  cpu->pc = ((cpu->opcode & 0x0FFF) + cpu->vReg[0]);
}

void RNDVxByte(chip8_t* cpu)
{
  srand(time(0));

  unsigned short rng = ((rand() & 256) & (cpu->opcode & 0x00FF));
  unsigned short regx = (cpu->opcode & 0x0F00) >> 8;
  cpu->vReg[regx] = rng;

  cpu->pc += 2;
}

void DRWVxVyNib(chip8_t* cpu)
{
  // x position to start drawing sprite
  unsigned short xPos = cpu->vReg[(cpu->opcode & 0x0F00) >> 8];
  // y position to start drawing sprite
  unsigned short yPos = cpu->vReg[(cpu->opcode & 0x00F0) >> 4];
  // how many lines is the sprite
  unsigned short height = (cpu->opcode & 0x000F);

  cpu->vReg[0xF] = 0;

  for (int yLine = 0; yLine < height; yLine++)
  {
    unsigned short sprite = cpu->memory[cpu->iReg + yLine];

    // iterate through sprite byte for collision
    for (int xLine = 0; xLine < 8; xLine++)
    {
      // if current bit is to be drawn
      if ((sprite & (0x80 >> xLine)) != 0)
      {
        // check if current bit at screen location is drawn (collision)
        if (cpu->gfx[(xPos + xLine + ((yPos + yLine) * 64))] == 1)
          cpu->vReg[0xF] = 1; // Set flag for collision
      }
    }
  }

  cpu->drawFlag = 1;
  cpu->pc += 2;
}

void SKPVx(chip8_t* cpu)
{
  unsigned short key = (cpu->opcode & 0x0F00) >> 8;

  if (cpu->keypad[key])
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void SKNPVx(chip8_t* cpu)
{
  unsigned short key = (cpu->opcode & 0x0F00) >> 8;

  if (!cpu->keypad[key])
    cpu->pc += 4;
  else
    cpu->pc += 2;
}

void LDVxDT(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;
  cpu->vReg[xReg] = cpu->delay_timer;

  cpu->pc += 2;  
}

void LDVxK(chip8_t* cpu)
{
  int key = 0;
  int found = 0;
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;

  // cycle through keypad to find if key is pressed, if key is pressed store in Vx
  while (!found || key < 16)
  {
    if (cpu->keypad[key] == 1)
    {
      cpu->vReg[xReg] = key;
      found = 1;
    }
    else
      key++;
  }

  // if key is pressed move on otherwise decrement pc and check again
  if (key == 16)
    cpu->pc -= 2;
  else
    cpu->pc += 2;
}

void LDDTVx(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;

  cpu->delay_timer = cpu->vReg[xReg];

  cpu->pc += 2;
}

void LDSTVx(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;

  cpu->sound_timer = cpu->vReg[xReg];

  cpu->pc += 2;
}

void ADDIVx(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;
  cpu->iReg += cpu->vReg[xReg];

  cpu->pc += 2;
}

void LDFVx(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;

  cpu->iReg = cpu->vReg[xReg] * 5;
  cpu->pc += 2;
}

void LDBVx(chip8_t* cpu)
{
  unsigned short xReg = (cpu->opcode & 0x0F00) >> 8;
  unsigned short value = cpu->vReg[xReg];

  // ones place
  cpu->memory[cpu->iReg + 2] = value % 10;
  value /= 10;

  // tens place
  cpu->memory[cpu->iReg + 1] = value % 10;
  value /= 10;

  // hundreds place
  cpu->memory[cpu->iReg] = value % 10;

  cpu->pc += 2;
}

void LDIVx(chip8_t* cpu)
{
  unsigned short maxReg = (cpu->opcode & 0x0F00) >> 8;

  for (int ii = 0; ii <= maxReg; ii++)
    cpu->memory[cpu->iReg + ii] = cpu->vReg[ii];

  cpu->pc += 2;
}

void LDVxI(chip8_t* cpu)
{
  unsigned short maxReg = (cpu->opcode & 0x0F00) >> 8;

  for (int ii = 0; ii <= maxReg; ii++)
    cpu->vReg[ii] = cpu->memory[cpu->iReg + ii];

  cpu->pc += 2;
}