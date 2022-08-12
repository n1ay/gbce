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

void cmd_8bit_inc(Emulator* emulator, uint8_t* register_ptr);

void cmd_8bit_dec(Emulator* emulator, uint8_t* register_ptr);

void cmd_8bit_reg_sub(Emulator* emulator, uint8_t* target_ptr, const uint8_t sub_value);

void cmd_8bit_reg_sub_carry(Emulator* emulator, uint8_t* target_ptr, const uint8_t sub_value);

void cmd_8bit_reg_add(Emulator* emulator, uint8_t* target_ptr, const uint8_t add_value);

void cmd_16bit_reg_add(Emulator* emulator, uint16_t* target_ptr, const uint16_t add_value);

void cmd_8bit_reg_add_carry(Emulator* emulator, uint8_t* target_ptr, const uint8_t add_value);

void cmd_8bit_reg_and(Emulator* emulator, uint8_t* target_ptr, const uint8_t value);

void cmd_8bit_reg_xor(Emulator* emulator, uint8_t* target_ptr, const uint8_t value);

void cmd_8bit_reg_or(Emulator* emulator, uint8_t* target_ptr, const uint8_t value);

void cmd_8bit_reg_cp(Emulator* emulator, const uint8_t target_ptr, const uint8_t value);
#endif
