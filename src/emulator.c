#include "emulator.h"

void init_emulator(Emulator* emulator) {
    init_cpu(&emulator->cpu);
    init_memory(&emulator->memory);
}

void emulate_op_code(uint8_t* program, Emulator* emulator) {
    uint8_t op_code = program[emulator->cpu.PC];
    uint8_t byte1 = program[emulator->cpu.PC + 1];
    uint8_t byte2 = program[emulator->cpu.PC + 2];
    uint8_t is_jump = 0;
    switch(program[emulator->cpu.PC]) {
        case 0x00: //NOP
            break;

        case 0x01: //LD BC,nn
            emulator->cpu.BC = merge_bytes(byte1, byte2);
            MOV_PC2;
            break;

        case 0x02: //LD (BC),A
            (*access_memory(emulator->memory, emulator->cpu.BC)) = emulator->cpu.A;
            break;

        case 0x03: //INC BC
            ++emulator->cpu.BC;
            break;

        case 0x04: //INC B
            cmd_8bit_inc(emulator, &emulator->cpu.B);
            break;

        case 0x05: //DEC B
            cmd_8bit_dec(emulator, &emulator->cpu.B);
            break;

        case 0x06: //LD B,n
            emulator->cpu.B = byte1;
            MOV_PC;
            break;

        case 0x07: //RLCA
            //TODO
            break;

        case 0x08: //LD (nn),SP
            *(access_memory(emulator->memory, merge_bytes(byte1, byte2))) = emulator->cpu.SP;
            MOV_PC2;
            break;

        case 0x09: //ADD HL,BC
            cmd_16bit_reg_add(emulator, &emulator->cpu.HL, emulator->cpu.BC);
            break;

        case 0x0a: //LD A,(BC)
            emulator->cpu.A = *(access_memory(emulator->memory, emulator->cpu.BC));
            break;

        case 0x0b: //DEC BC
            --emulator->cpu.BC;
            break;

        case 0x0c: //INC C
            cmd_8bit_inc(emulator, &emulator->cpu.C);
            break;

        case 0x0d: //DEC C
            cmd_8bit_dec(emulator, &emulator->cpu.C);
            break;

        case 0x0e: //LD C,n
            emulator->cpu.C = byte1;
            MOV_PC;
            break;

        case 0x0f: //RRCA
            //TODO
            break;

        case 0x10: //STOP
            MOV_PC;
            break;

        case 0x11: //LD DE,nn
            emulator->cpu.DE = merge_bytes(byte1, byte2);
            MOV_PC2;
            break;

        case 0x12: //LD (DE),A
            (*access_memory(emulator->memory, emulator->cpu.DE)) = emulator->cpu.A;
            break;

        case 0x13: //INC DE
            ++emulator->cpu.DE;
            break;

        case 0x14: //INC D
            cmd_8bit_inc(emulator, &emulator->cpu.D);
            break;

        case 0x15: //DEC D
            cmd_8bit_dec(emulator, &emulator->cpu.D);
            break;

        case 0x16: //LD D,n
            emulator->cpu.D = byte1;
            MOV_PC;
            break;

        case 0x17: //RLA
            //TODO
            break;

        case 0x18: //JR n
            MOV_PC;
            emulator->cpu.PC += byte1;
            is_jump = 1;
            break;

        case 0x19: //ADD HL,DE
            cmd_16bit_reg_add(emulator, &emulator->cpu.HL, emulator->cpu.DE);
            break;

        case 0x1a: //LD A,(DE)
            emulator->cpu.A = *(access_memory(emulator->memory, emulator->cpu.DE));
            break;

        case 0x1b: //DEC DE
            --emulator->cpu.DE;
            break;

        case 0x1c: //INC E
            cmd_8bit_inc(emulator, &emulator->cpu.E);
            break;

        case 0x1d: //DEC E
            cmd_8bit_dec(emulator, &emulator->cpu.E);
            break;

        case 0x1e: //LD E,n
            emulator->cpu.E = byte1;
            MOV_PC;
            break;

        case 0x1f: //RRA
            //TODO
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

        case 0xfa: //LD A,(nn)
            emulator->cpu.A = *(access_memory(emulator->memory, merge_bytes(byte1, byte2)));
            MOV_PC2;
            break;

        case 0x3e: //LD A,n
            emulator->cpu.A = byte1;
            MOV_PC;
            break;

        case 0x40: //LD B,B
            emulator->cpu.B = emulator->cpu.B;
            break;

        case 0x41: //LD B,C
            emulator->cpu.B = emulator->cpu.C;
            break;

        case 0x42: //LD B,D
            emulator->cpu.B = emulator->cpu.D;
            break;

        case 0x43: //LD B,E
            emulator->cpu.B = emulator->cpu.E;
            break;

        case 0x44: //LD B,H
            emulator->cpu.B = emulator->cpu.H;
            break;

        case 0x45: //LD B,L
            emulator->cpu.B = emulator->cpu.L;
            break;

        case 0x46: //LD B,(HL)
            emulator->cpu.B = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x48: //LD C,B
            emulator->cpu.C = emulator->cpu.B;
            break;

        case 0x49: //LD C,C
            emulator->cpu.C = emulator->cpu.C;
            break;

        case 0x4a: //LD C,D
            emulator->cpu.C = emulator->cpu.D;
            break;

        case 0x4b: //LD C,E
            emulator->cpu.C = emulator->cpu.E;
            break;

        case 0x4c: //LD C,H
            emulator->cpu.C = emulator->cpu.H;
            break;

        case 0x4d: //LD C,L
            emulator->cpu.C = emulator->cpu.L;
            break;

        case 0x4e: //LD C,(HL)
            emulator->cpu.C = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x50: //LD D,B
            emulator->cpu.D = emulator->cpu.B;
            break;

        case 0x51: //LD D,C
            emulator->cpu.D = emulator->cpu.C;
            break;

        case 0x52: //LD D,D
            emulator->cpu.D = emulator->cpu.D;
            break;

        case 0x53: //LD D,E
            emulator->cpu.D = emulator->cpu.E;
            break;

        case 0x54: //LD D,H
            emulator->cpu.D = emulator->cpu.H;
            break;

        case 0x55: //LD D,L
            emulator->cpu.D = emulator->cpu.L;
            break;

        case 0x56: //LD D,(HL)
            emulator->cpu.D = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x58: //LD E,B
            emulator->cpu.E = emulator->cpu.B;
            break;

        case 0x59: //LD E,C
            emulator->cpu.E = emulator->cpu.C;
            break;

        case 0x5a: //LD E,D
            emulator->cpu.E = emulator->cpu.D;
            break;

        case 0x5b: //LD E,E
            emulator->cpu.D = emulator->cpu.E;
            break;

        case 0x5c: //LD E,H
            emulator->cpu.D = emulator->cpu.H;
            break;

        case 0x5d: //LD E,L
            emulator->cpu.D = emulator->cpu.L;
            break;

        case 0x5e: //LD E,(HL)
            emulator->cpu.E = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x60: //LD H,B
            emulator->cpu.H = emulator->cpu.B;
            break;

        case 0x61: //LD H,C
            emulator->cpu.H = emulator->cpu.C;
            break;

        case 0x62: //LD H,D
            emulator->cpu.H = emulator->cpu.D;
            break;

        case 0x63: //LD H,E
            emulator->cpu.H = emulator->cpu.E;
            break;

        case 0x64: //LD H,H
            emulator->cpu.H = emulator->cpu.H;
            break;

        case 0x65: //LD H,L
            emulator->cpu.H = emulator->cpu.L;
            break;

        case 0x66: //LD H,(HL)
            emulator->cpu.H = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x68: //LD L,B
            emulator->cpu.L = emulator->cpu.B;
            break;

        case 0x69: //LD L,C
            emulator->cpu.L = emulator->cpu.C;
            break;

        case 0x6a: //LD L,D
            emulator->cpu.L = emulator->cpu.D;
            break;

        case 0x6b: //LD L,E
            emulator->cpu.L = emulator->cpu.E;
            break;

        case 0x6c: //LD L,H
            emulator->cpu.L = emulator->cpu.H;
            break;

        case 0x6d: //LD L,L
            emulator->cpu.L = emulator->cpu.L;
            break;

        case 0x6e: //LD L,(HL)
            emulator->cpu.L = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x70: //LD (HL),B
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.B;
            break;

        case 0x71: //LD (HL),C
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.C;
            break;

        case 0x72: //LD (HL),D
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.D;
            break;

        case 0x73: //LD (HL),E
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.E;
            break;

        case 0x74: //LD (HL),H
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.H;
            break;

        case 0x75: //LD (HL),L
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.L;
            break;

        case 0x76: //LD (HL),n
            *(access_memory(emulator->memory, emulator->cpu.HL)) = byte1;
            MOV_PC;
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

void cmd_8bit_inc(Emulator* emulator, uint8_t* register_ptr) {
    unset_flag(&emulator->cpu, FLAG_N);
    if (add_get_carry_bit(*register_ptr, 0x01, BIT3)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    ++(*register_ptr);
    if (!(*register_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_dec(Emulator* emulator, uint8_t* register_ptr) {
    set_flag(&emulator->cpu, FLAG_N);
    if (!subtract_get_borrow_bit(*register_ptr, 0x01, BIT3)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    --(*register_ptr);
    if(!(*register_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_16bit_reg_add(Emulator* emulator, uint16_t* target_ptr, const uint16_t add_value) {
    unset_flag(&emulator->cpu, FLAG_N);
    if (add_get_carry_bit(*target_ptr, add_value, BIT11)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (add_get_carry_bit(*target_ptr, add_value, BIT15)) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    (*target_ptr) += add_value;
}
