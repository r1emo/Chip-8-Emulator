#ifndef OPCODE_H
#define OPCODE_H
#include "chip8.h"

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
void ORVxVy(chip8_t* cpu);

#endif