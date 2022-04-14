#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

#include "byte.h"

typedef struct Cpu {
    union {
        struct {
            uint8_t A;
            uint8_t F;
        };
        uint16_t AF;
    };

    union {
        struct {
            uint8_t B;
            uint8_t C;
        };
        uint16_t BC;
    };

    union {
        struct {
            uint8_t D;
            uint8_t E;
        };
        uint16_t DE;
    };

    union {
        struct {
            uint8_t H;
            uint8_t L;
        };
        uint16_t HL;
    };

    uint16_t PC;
    uint16_t SP;
} Cpu;

typedef enum CpuFlag {
    FLAG_Z = BIT7,
    FLAG_N = BIT6,
    FLAG_H = BIT5,
    FLAG_C = BIT4
} CpuFlag;

void init_cpu(Cpu* cpu_ptr);

uint8_t get_flag(const Cpu cpu, CpuFlag flag);
void set_flag(Cpu* cpu_ptr, CpuFlag flag);
void unset_flag(Cpu* cpu_ptr, CpuFlag flag);

#endif
