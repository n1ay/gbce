#include "emulator.h"
#include "byte.h"

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
            //TODO
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

        case 0x20: //JR NZ,n
            MOV_PC;
            if (!get_flag(emulator->cpu, FLAG_Z)) {
                emulator->cpu.PC += byte1;
                is_jump = 1;
            }
            break;

        case 0x21: //LD HL,nn
            emulator->cpu.HL = merge_bytes(byte1, byte2);
            MOV_PC2;
            break;

        case 0x22: // LD (HL+),A
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.A;
            ++emulator->cpu.HL;
            break;

        case 0x23: //INC HL
            ++emulator->cpu.HL;
            break;

        case 0x24: //INC H
            cmd_8bit_inc(emulator, &emulator->cpu.H);
            break;

        case 0x25: //DEC H
            cmd_8bit_dec(emulator, &emulator->cpu.H);
            break;

        case 0x26: //LD H,n
            emulator->cpu.H = byte1;
            MOV_PC;
            break;

        case 0x27: //DAA
            //TODO
            break;

        case 0x28: //JR Z,n
            MOV_PC;
            if (get_flag(emulator->cpu, FLAG_Z)) {
                emulator->cpu.PC += byte1;
                is_jump = 1;
            }
            break;

        case 0x29: //ADD HL,HL
            cmd_16bit_reg_add(emulator, &emulator->cpu.HL, emulator->cpu.HL);
            break;

        case 0x2a: //LD A,(HL+)
            emulator->cpu.A = *(access_memory(emulator->memory, emulator->cpu.HL));
            ++emulator->cpu.HL;
            break;

        case 0x2b: //DEC HL
            --emulator->cpu.HL;
            break;

        case 0x2c: //INC L
            cmd_8bit_inc(emulator, &emulator->cpu.L);
            break;

        case 0x2d: //DEC L
            cmd_8bit_dec(emulator, &emulator->cpu.L);
            break;

        case 0x2e: //LD L,n
            emulator->cpu.L = byte1;
            MOV_PC;
            break;

        case 0x2f: //CPL
            //TODO
            break;

        case 0x30: //JR NC,n
            MOV_PC;
            if (!get_flag(emulator->cpu, FLAG_C)) {
                emulator->cpu.PC += byte1;
                is_jump = 1;
            }
            break;

        case 0x31: //LD SP,nn
            emulator->cpu.SP = merge_bytes(byte1, byte2);
            MOV_PC2;
            break;

        case 0x32: // LD (HL-),A
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.A;
            --emulator->cpu.HL;
            break;

        case 0x33: //INC SP
            ++emulator->cpu.SP;
            break;

        case 0x34: //INC (HL)
            cmd_8bit_inc(emulator, access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x35: //DEC (HL)
            cmd_8bit_dec(emulator, access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x36: //LD (HL),n
            *(access_memory(emulator->memory, emulator->cpu.HL)) = byte1;
            MOV_PC;
            break;

        case 0x37: //SCF
            //TODO
            break;

        case 0x38: //JR C,n
            MOV_PC;
            if (get_flag(emulator->cpu, FLAG_C)) {
                emulator->cpu.PC += byte1;
                is_jump = 1;
            }
            break;

        case 0x39: //ADD HL,SP
            cmd_16bit_reg_add(emulator, &emulator->cpu.HL, emulator->cpu.SP);
            break;

        case 0x3a: //LD A,(HL-)
            emulator->cpu.A = *(access_memory(emulator->memory, emulator->cpu.HL));
            --emulator->cpu.HL;
            break;

        case 0x3b: //DEC SP
            --emulator->cpu.SP;
            break;

        case 0x3c: //INC A
            cmd_8bit_inc(emulator, &emulator->cpu.A);
            break;

        case 0x3d: //DEC A
            cmd_8bit_dec(emulator, &emulator->cpu.A);
            break;

        case 0x3e: //LD A,n
            emulator->cpu.A = byte1;
            MOV_PC;
            break;

        case 0x3f: //CCF
            //TODO
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

        case 0x47: //LD B,A
            emulator->cpu.B = emulator->cpu.A;
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

        case 0x4f: //LD C,A
            emulator->cpu.C = emulator->cpu.A;
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

        case 0x57: //LD D,A
            emulator->cpu.D = emulator->cpu.A;
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
            emulator->cpu.E = emulator->cpu.E;
            break;

        case 0x5c: //LD E,H
            emulator->cpu.E = emulator->cpu.H;
            break;

        case 0x5d: //LD E,L
            emulator->cpu.E = emulator->cpu.L;
            break;

        case 0x5e: //LD E,(HL)
            emulator->cpu.E = *(access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x5f: //LD E,A
            emulator->cpu.E = emulator->cpu.A;
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

        case 0x67: //LD H,A
            emulator->cpu.H = emulator->cpu.A;
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

        case 0x6f: //LD L,A
            emulator->cpu.L = emulator->cpu.A;
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

        case 0x76: //HALT
            //TODO
            break;

        case 0x77: //LD (HL),A
            *(access_memory(emulator->memory, emulator->cpu.HL)) = emulator->cpu.A;
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

        case 0x7f: //LD A,A
            emulator->cpu.A = emulator->cpu.A;
            break;

        case 0x80: //ADD A,B
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0x81: //ADD A,C
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0x82: //ADD A,D
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0x83: //ADD A,E
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0x84: //ADD A,H
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0x85: //ADD A,L
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0x86: //ADD A,(HL)
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, *(access_memory(emulator->memory, emulator->cpu.HL)));
            break;

        case 0x87: //ADD A,A
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0x88: //ADC A,B
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0x89: //ADC A,C
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0x8a: //ADC A,D
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0x8b: //ADC A,E
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0x8c: //ADC A,H
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0x8d: //ADC A,L
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0x8e: //ADC A,(HL)
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, *(access_memory(emulator->memory, emulator->cpu.HL)));
            break;

        case 0x8f: //ADC A,A
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0x90: //SUB B
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0x91: //SUB C
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0x92: //SUB D
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0x93: //SUB E
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0x94: //SUB H
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0x95: //SUB L
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0x96: //SUB (HL)
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x97: //SUB A
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0x98: //SBC A,B
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0x99: //SBC A,C
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0x9a: //SBC A,D
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0x9b: //SBC A,E
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0x9c: //SBC A,H
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0x9d: //SBC A,L
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0x9e: //SBC A,(HL)
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0x9f: //SBC A,A
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0xa0: //AND B
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0xa1: //AND C
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0xa2: //AND D
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0xa3: //AND E
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0xa4: //AND H
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0xa5: //AND L
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0xa6: //AND (HL)
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0xa7: //AND A
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0xa8: //XOR B
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0xa9: //XOR C
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0xaa: //XOR D
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0xab: //XOR E
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0xac: //XOR H
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0xad: //XOR L
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0xae: //XOR (HL)
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0xaf: //XOR A
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0xb0: //OR B
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.B);
            break;

        case 0xb1: //OR C
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.C);
            break;

        case 0xb2: //OR D
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.D);
            break;

        case 0xb3: //OR E
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.E);
            break;

        case 0xb4: //OR H
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.H);
            break;

        case 0xb5: //OR L
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.L);
            break;

        case 0xb6: //OR (HL)
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0xb7: //OR A
            cmd_8bit_reg_or(emulator, &emulator->cpu.A, emulator->cpu.A);
            break;

        case 0xb8: //CP B
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.B);
            break;

        case 0xb9: //CP C
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.C);
            break;

        case 0xba: //CP D
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.D);
            break;

        case 0xbb: //CP E
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.E);
            break;

        case 0xbc: //CP H
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.H);
            break;

        case 0xbd: //CP L
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.L);
            break;

        case 0xbe: //CP (HL)
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, *access_memory(emulator->memory, emulator->cpu.HL));
            break;

        case 0xbf: //CP A
            cmd_8bit_reg_cp(emulator, emulator->cpu.A, emulator->cpu.A);
            break;

        case 0xc0: //RET NZ
            if (!get_flag(emulator->cpu, FLAG_Z)) {
                cmd_return(emulator);
            }
            break;

        case 0xc1: //POP BC
            cmd_pop(emulator, &emulator->cpu.BC);
            break;

        case 0xc2: //JP NZ,nn
            MOV_PC2;
            if (!get_flag(emulator->cpu, FLAG_Z)) {
                emulator->cpu.PC = merge_bytes(byte1, byte2);
                is_jump = 1;
            }
            break;

        case 0xc3: //JP nn
            MOV_PC2;
            emulator->cpu.PC = merge_bytes(byte1, byte2);
            is_jump = 1;
            break;

        case 0xc4: //CALL NZ,nn
            MOV_PC2;
            if (!get_flag(emulator->cpu, FLAG_Z)) {
                cmd_call(emulator, merge_bytes(byte1, byte2));
                is_jump = 1;
            }
            break;

        case 0xc5: //PUSH BC
            cmd_push(emulator, emulator->cpu.BC);
            break;

        case 0xc6: //ADD A,n
            cmd_8bit_reg_add(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xc7: //RST 00H
            //TODO
            break;

        case 0xc8: //RET Z
            if (get_flag(emulator->cpu, FLAG_Z)) {
                cmd_return(emulator);
            }
            break;

        case 0xc9: //RET
            cmd_return(emulator);
            break;

        case 0xca: //JP Z,nn
            MOV_PC2;
            if (get_flag(emulator->cpu, FLAG_Z)) {
                emulator->cpu.PC = merge_bytes(byte1, byte2);
                is_jump = 1;
            }
            break;

        case 0xcb: //0xcb prefix
            //TODO
            break;

        case 0xcc: //CALL Z,nn
            MOV_PC2;
            if (get_flag(emulator->cpu, FLAG_Z)) {
                cmd_call(emulator, merge_bytes(byte1, byte2));
                is_jump = 1;
            }
            break;

        case 0xcd: //CALL nn
            MOV_PC2;
            cmd_call(emulator, merge_bytes(byte1, byte2));
            is_jump = 1;
            break;

        case 0xce: //ADC A,n
            cmd_8bit_reg_add_carry(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xcf: //RST 08H
            //TODO
            break;

        case 0xd0: //RET NC
            if (!get_flag(emulator->cpu, FLAG_C)) {
                cmd_return(emulator);
            }
            break;

        case 0xd1: //POP DE
            cmd_pop(emulator, &emulator->cpu.DE);
            break;

        case 0xd2: //JP NC,nn
            MOV_PC2;
            if (!get_flag(emulator->cpu, FLAG_C)) {
                emulator->cpu.PC = merge_bytes(byte1, byte2);
                is_jump = 1;
            }
            break;

        case 0xd4: //CALL NC,nn
            MOV_PC2;
            if (!get_flag(emulator->cpu, FLAG_C)) {
                cmd_call(emulator, merge_bytes(byte1, byte2));
                is_jump = 1;
            }
            break;

        case 0xd5: //PUSH DE
            cmd_push(emulator, emulator->cpu.DE);
            break;

        case 0xd6: //SUB n
            cmd_8bit_reg_sub(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xd7: //RST 10H
            //TODO
            break;

        case 0xd8: //RET C
            if (get_flag(emulator->cpu, FLAG_C)) {
                cmd_return(emulator);
            }
            break;

        case 0xd9: //RETI
            //TODO
            break;

        case 0xda: //JP C,nn
            MOV_PC2;
            if (get_flag(emulator->cpu, FLAG_C)) {
                emulator->cpu.PC = merge_bytes(byte1, byte2);
                is_jump = 1;
            }
            break;

        case 0xdc: //CALL C,nn
            MOV_PC2;
            if (get_flag(emulator->cpu, FLAG_C)) {
                cmd_call(emulator, merge_bytes(byte1, byte2));
                is_jump = 1;
            }
            break;

        case 0xde: //SBC A,n
            cmd_8bit_reg_sub_carry(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xdf: //RST 18H
            //TODO
            break;

        case 0xe0: //LDH (n),A
            *access_memory(emulator->memory, 0xff00 + byte1) = emulator->cpu.A;
            MOV_PC;
            break;

        case 0xe1: //POP HL
            cmd_pop(emulator, &emulator->cpu.HL);
            break;

        case 0xe2: //LD (C),A
            *access_memory(emulator->memory, 0xff00 + emulator->cpu.C) = emulator->cpu.A;
            break;

        case 0xe5: //PUSH HL
            cmd_push(emulator, emulator->cpu.HL);
            break;

        case 0xe6: //AND n
            cmd_8bit_reg_and(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xe7: //RST 20H
            //TODO
            break;

        case 0xe8: //ADD SP,n
            cmd_16bit_reg_add(emulator, &emulator->cpu.SP, byte1);
            MOV_PC;
            break;

        case 0xe9: //JP (HL)
            emulator->cpu.PC = emulator->cpu.HL;
            is_jump = 1;
            break;

        case 0xea: //LD (nn),A
            emulator->cpu.A = *access_memory(emulator->memory, merge_bytes(byte1, byte2));
            MOV_PC2;
            break;

        case 0xee: //XOR n
            cmd_8bit_reg_xor(emulator, &emulator->cpu.A, byte1);
            MOV_PC;
            break;

        case 0xef: //RST 28H
            //TODO
            break;

        case 0xfa: //LD A,(nn)
            emulator->cpu.A = *(access_memory(emulator->memory, merge_bytes(byte1, byte2)));
            MOV_PC2;
            break;

        default:
            fprintf(stderr, "Unrecognised opcode: %#04x\n", op_code);
            break;
    }

    if (!is_jump) {
        MOV_PC;
    }
}

void cmd_8bit_inc(Emulator* emulator, uint8_t* register_ptr) {
    unset_flag(&emulator->cpu, FLAG_N);
    if (get_8b_half_carry_bit(*register_ptr, 0x01)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    ++(*register_ptr);
    if (!(*register_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_dec(Emulator* emulator, uint8_t* register_ptr) {
    set_flag(&emulator->cpu, FLAG_N);
    if (!get_8b_half_borrow_bit(*register_ptr, 0x01)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    --(*register_ptr);
    if(!(*register_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_reg_sub(Emulator* emulator, uint8_t* target_ptr, const uint8_t sub_value) {
    set_flag(&emulator->cpu, FLAG_N);
    if (!get_8b_half_borrow_bit(*target_ptr, sub_value)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (!get_8b_borrow_bit(*target_ptr, sub_value)) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    *target_ptr -= sub_value;
    if(!(*target_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_reg_sub_carry(Emulator* emulator, uint8_t* target_ptr, const uint8_t sub_value) {
    uint8_t carry_bit = get_flag(emulator->cpu, FLAG_C);
    set_flag(&emulator->cpu, FLAG_N);
    if (!get_8b_half_borrow_bit(*target_ptr, sub_value) || (carry_bit && !get_8b_half_borrow_bit(*target_ptr - sub_value, carry_bit))) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (!get_8b_borrow_bit(*target_ptr, sub_value) || (carry_bit && !get_8b_borrow_bit(*target_ptr - sub_value, carry_bit))) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    *target_ptr -= sub_value;
    *target_ptr -= carry_bit;
    if(!(*target_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_reg_add(Emulator* emulator, uint8_t* target_ptr, const uint8_t add_value) {
    unset_flag(&emulator->cpu, FLAG_N);
    if (get_8b_half_carry_bit(*target_ptr, add_value)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (get_8b_carry_bit(*target_ptr, add_value)) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    *target_ptr += add_value;
    if (!(*target_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_16bit_reg_add(Emulator* emulator, uint16_t* target_ptr, const uint16_t add_value) {
    unset_flag(&emulator->cpu, FLAG_N);
    if (get_16b_half_carry_bit(*target_ptr, add_value)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (get_16b_carry_bit(*target_ptr, add_value)) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    (*target_ptr) += add_value;
}


void cmd_8bit_reg_add_carry(Emulator* emulator, uint8_t* target_ptr, const uint8_t add_value) {
    uint8_t carry_bit = get_flag(emulator->cpu, FLAG_C);
    unset_flag(&emulator->cpu, FLAG_N);
    if (get_8b_half_carry_bit(*target_ptr, add_value) || (carry_bit && get_8b_half_carry_bit(*target_ptr + add_value, carry_bit))) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (get_8b_carry_bit(*target_ptr, add_value) || (carry_bit && get_8b_carry_bit(*target_ptr + add_value, carry_bit))) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    *target_ptr += add_value;
    *target_ptr += carry_bit;
    if (!(*target_ptr)) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
}

void cmd_8bit_reg_and(Emulator* emulator, uint8_t* target_ptr, const uint8_t value) {
    *target_ptr = (*target_ptr & value);
    if (!*target_ptr) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
    unset_flag(&emulator->cpu, FLAG_N);
    set_flag(&emulator->cpu, FLAG_H);
    unset_flag(&emulator->cpu, FLAG_C);
}

void cmd_8bit_reg_xor(Emulator* emulator, uint8_t* target_ptr, const uint8_t value) {
    *target_ptr = (*target_ptr ^ value);
    if (!*target_ptr) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
    unset_flag(&emulator->cpu, FLAG_N);
    unset_flag(&emulator->cpu, FLAG_H);
    unset_flag(&emulator->cpu, FLAG_C);
}

void cmd_8bit_reg_or(Emulator* emulator, uint8_t* target_ptr, const uint8_t value) {
    *target_ptr = (*target_ptr | value);
    if (!*target_ptr) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
    unset_flag(&emulator->cpu, FLAG_N);
    unset_flag(&emulator->cpu, FLAG_H);
    unset_flag(&emulator->cpu, FLAG_C);
}

void cmd_8bit_reg_cp(Emulator* emulator, const uint8_t target_ptr, const uint8_t value) {
    if (target_ptr == value) {
        set_flag(&emulator->cpu, FLAG_Z);
    }
    if (!get_8b_half_borrow_bit(target_ptr, value)) {
        set_flag(&emulator->cpu, FLAG_H);
    }
    if (!get_8b_borrow_bit(target_ptr, value)) {
        set_flag(&emulator->cpu, FLAG_C);
    }
    set_flag(&emulator->cpu, FLAG_N);
}

void cmd_call(Emulator* emulator, const uint16_t jump_address) {
    cmd_push(emulator, emulator->cpu.PC);
    emulator->cpu.PC = jump_address;
}

void cmd_return(Emulator* emulator) {
    cmd_pop(emulator, &emulator->cpu.PC);
}

void cmd_pop(Emulator* emulator, uint16_t* target_ptr) {
    *target_ptr = *access_memory(emulator->memory, emulator->cpu.SP);
    emulator->cpu.SP += 2;
}

void cmd_push(Emulator* emulator, const uint16_t target_ptr) {
    emulator->cpu.SP -= 2;
    *access_memory(emulator->memory, emulator->cpu.SP) = target_ptr;
}

