#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "cpu.h"
#include "memory.h"

#define MOV_PC (emulator->cpu.PC += 1)
#define MOV_PC2 (emulator->cpu.PC += 2)

typedef struct Emulator {
    Cpu cpu;
    Memory memory;
} Emulator;

void init_emulator(Emulator* emulator);

void emulate_op_code(uint8_t* program, Emulator* emulator);

#endif
