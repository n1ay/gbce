#include "emulator.h"

void init_emulator(Emulator* emulator) {
    init_cpu(&(emulator->cpu));
    init_memory(&(emulator->memory));
}

void emulate_op_code(uint8_t* program, Emulator* emulator) {
    uint8_t op_code = program[emulator->cpu.PC];
    uint8_t byte1 = program[emulator->cpu.PC + 1];
    uint8_t byte2 = program[emulator->cpu.PC + 2];
    uint8_t is_jump = 0;
    switch(program[emulator->cpu.PC]) {
        case 0x00: //NOP
            break;

        case 0x06: //LD B,n
            emulator->cpu.B = byte1;
            MOV_PC;
            break;

        case 0x0e: //LD C,n
            emulator->cpu.C = byte1;
            MOV_PC;
            break;

        case 0x16: //LD D,n
            emulator->cpu.D = byte1;
            MOV_PC;
            break;

        case 0x1e: //LD E,n
            emulator->cpu.E = byte1;
            MOV_PC;
            break;

        case 0x26: //LD H,n
            emulator->cpu.H = byte1;
            MOV_PC;
            break;

        case 0x2e: //LD L,n
            emulator->cpu.L = byte1;
            MOV_PC;
            break;

        case 0x7f: //LD A,A
            emulator->cpu.A = emulator->cpu.A;
            break;

        case 0x78: //LD A,B
            emulator->cpu.A = emulator->cpu.B;
            break;

        case 0x79: //LD A,C
            emulator->cpu.A = emulator->cpu.C;
            break;

        case 0x7a: //LD A,D
            emulator->cpu.A = emulator->cpu.D;
            break;

        case 0x7b: //LD A,E
            emulator->cpu.A = emulator->cpu.E;
            break;

        case 0x7c: //LD A,H
            emulator->cpu.A = emulator->cpu.H;
            break;

        case 0x7d: //LD A,L
            emulator->cpu.A = emulator->cpu.L;
            break;

        case 0x7e: //LD A,(HL)
            emulator->cpu.A = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        default:
            fprintf(stderr, "Unrecognised opcode: %#04x\n", op_code);
            break;
    }

    if (is_jump) {
        return;
    } else {
        MOV_PC;
    }
}
