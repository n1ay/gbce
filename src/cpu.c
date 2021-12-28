#include "cpu.h"

void init_cpu(Cpu* cpu_ptr) {
    cpu_ptr -> A = 0x01;
    cpu_ptr -> F = 0x00;
    cpu_ptr -> B = 0xff;
    cpu_ptr -> C = 0x13;
    cpu_ptr -> D = 0x00;
    cpu_ptr -> E = 0xc1;
    cpu_ptr -> H = 0x84;
    cpu_ptr -> L = 0x03;
    cpu_ptr -> PC = 0x0100;
    cpu_ptr -> SP = 0xfffe;
}

uint8_t get_flag(const Cpu cpu, CpuFlag flag) {
    return get_bit(cpu.F, (Bit) flag);
}
