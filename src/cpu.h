#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

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

void init_cpu(Cpu* cpu_ptr);

#endif
