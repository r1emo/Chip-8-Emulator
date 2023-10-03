#include "headers/chip8.h"
#include <fstream>
#include <iostream>

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

chip8::chip8()
{
  pc = 0x200;
  opcode = 0;
  iReg = 0;
  sp = 0;

  // clear display
  for (int ii = 0; ii < (64*32); ii++)
    gfx[ii] = 0;

  // clear registers v0-vF
  for (int ii = 0; ii < 16; ii++)
    vReg[ii] = 0;

  for (int ii = 0; ii < 4096; ii++)
    memory[ii] = 0;
  
  // load fontset
  for (int ii = 0; ii < 80; ii++)
    memory[ii] = chip8_fontset[ii];

  // TODO: reset timers
}

int chip8::loadGame(std::string fileName)
{
  int ret = -1;

  std::ifstream rom;
  rom.open(fileName, std::ios::binary | std::ios::ate);

  if (rom.is_open())
  {
    // get file size
    std::streampos buffer_size = rom.tellg();
    char* buffer = new char[buffer_size];

    // read file
    rom.seekg(0, std::ios::beg);
    rom.read(buffer, buffer_size);
    rom.close();

    // load file into memory
    for (int ii = 0; ii < buffer_size; ii++)
      memory[0x200 + ii] = buffer[ii];
  
    delete[] buffer;
    ret = 0;
  }

  return ret;
}

void chip8::CLS()
{
  // clear display
  for (int ii = 0; ii < (64*32); ii++)
    gfx[ii] = 0;
}

void chip8::RET()
{
  pc = stack[sp];
  --sp;
}

void chip8::SYSaddr()
{
  pc = opcode & 0x0FFF;
}

void chip8::JPaddr()
{
  pc = opcode & 0x0FFF;
}

void chip8::CALLaddr()
{
  ++sp;
  stack[sp] = pc;
  pc = opcode & 0x0FFF;
}

void chip8::SEVxByte()
{
  if (vReg[opcode & 0x0F00] == (opcode & 0x00FF))
  {
    pc += 2;
  }
}

void chip8::SNEVxByte()
{
  if (vReg[opcode & 0x0F00] != (opcode & 0x00FF))
  {
    pc += 2;
  }
}

void chip8::SEVxVy()
{
  if (vReg[opcode & 0x0F00] == vReg[opcode & 0x00F0])
  {
    pc += 2;
  }
}