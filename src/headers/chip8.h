#ifndef CHIP8_H
#define CHIP8_H

#include <string>

class chip8
{
  public:
    chip8();
    int loadGame(std::string fileName);

  private:
    // current opcode
    unsigned short opcode;

    unsigned char memory[4096];
    
    // registers
    unsigned char vReg[16];
    unsigned short iReg;
    
    // program counter
    unsigned short pc;

    // graphics shiz
    unsigned char gfx[64*32];
    unsigned char drawFlag;

    // timers
    unsigned char delay_timer;
    unsigned char sound_timer;

    // stack shiz
    unsigned short stack[16];
    unsigned short sp;

    unsigned char key[16];

    // op code functions
    void CLS();
    void RET();
    void SYSaddr();
    void JPaddr();
    void CALLaddr();
    void SEVxByte();
    void SNEVxByte();
    void SEVxVy();
};

#endif