#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

#include "byte.h"

typedef struct Cpu {
    uint8_t A;
    uint8_t F;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
    uint16_t PC;
    uint16_t SP;
} Cpu;

typedef enum Flag {
    Z = BIT7,
    N = BIT6,
    H = BIT5,
    C = BIT4
} Flag;

void init_cpu(Cpu* cpu_ptr);

uint8_t get_flag(const Cpu cpu, Flag flag);

#endif
