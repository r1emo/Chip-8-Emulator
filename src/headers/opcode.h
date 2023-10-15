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
void ANDVxVy(chip8_t* cpu);
void XORVxVy(chip8_t* cpu);
void ADDVxVy(chip8_t* cpu);
void SUBVxVy(chip8_t* cpu);
void SHRVx(chip8_t* cpu);
void SUBNVxVy(chip8_t* cpu);
void SHLVx(chip8_t* cpu);
void SNEVxVy(chip8_t* cpu);
void LDI(chip8_t* cpu);
void JPV0(chip8_t* cpu);
void RNDVxByte(chip8_t* cpu);
void DXNY(chip8_t* cpu);

#endif