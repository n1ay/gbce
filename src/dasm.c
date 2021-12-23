#include "dasm.h"

void hexdump(int fd) {
    uint8_t* buffer;
    ssize_t read_bytes;

    buffer = (uint8_t*) malloc(BUFSIZE);
    memset(buffer, 0, BUFSIZE);
    read_bytes = read(fd, buffer, BUFSIZE);
    if (read_bytes <= 0 ) {
        fprintf(stderr, "Could not read file[fd=%d] content\n", fd);
        return;
    }

    if (read(fd, buffer, BUFSIZE) > 0 ) {
        fprintf(stderr, "Failed to load whole file[fd=%d] at once\n", fd);
        return;
    }

    ssize_t byte_num = 0;
    while (byte_num < read_bytes) {
        ssize_t i = 0;
        while (i < 16 && byte_num < read_bytes) {
            if ((i == 15) || (byte_num == (read_bytes - 1))) {
                printf ("%02x", buffer[byte_num]);
            } else {
                printf ("%02x ", buffer[byte_num]);
            }
            byte_num++;
            i++;
        }
        printf("\n");
    }
}

void dasm(int fd) {
    uint8_t* buffer;
    ssize_t read_bytes;

    buffer = (uint8_t*) malloc(BUFSIZE);
    memset(buffer, 0, BUFSIZE);
    read_bytes = read(fd, buffer, BUFSIZE);
    if (read_bytes <= 0 ) {
        fprintf(stderr, "Could not read file[fd=%d] content\n", fd);
        return;
    }

    if (read(fd, buffer, BUFSIZE) > 0 ) {
        fprintf(stderr, "Failed to load whole file[fd=%d] at once\n", fd);
        return;
    }

    ssize_t byte_index = 0;
    while (byte_index < read_bytes) {
        printf("%6lx | ", byte_index);
        switch(buffer[byte_index]) {
            // 0x00 - 0x0f
            case 0x00: printf("NOP\n"); break;
            case 0x01: printf("LD BC,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0x02: printf("LD BC,A\n"); break;
            case 0x03: printf("INC BC\n"); break;
            case 0x04: printf("INC B\n"); break;
            case 0x05: printf("DEC B\n"); break;
            case 0x06: printf("LD B,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x07: printf("RLCA\n"); break;
            case 0x08: printf("LD (%x %x),SP\n", B2_VAL); B2_MOV; break;
            case 0x09: printf("ADD HL,BC\n"); break;
            case 0x0a: printf("ADD A,BC\n"); break;
            case 0x0b: printf("DEC BC\n"); break;
            case 0x0c: printf("INC C\n"); break;
            case 0x0d: printf("DEC C\n"); break;
            case 0x0e: printf("LD C,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x0f: printf("RRCA\n"); break;

            //0x10 - 0x1f
            case 0x10: printf("STOP (%x)\n", B1_VAL); B1_MOV; break;
            case 0x11: printf("LD DE,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0x12: printf("LD DE,A\n"); break;
            case 0x13: printf("INC DE\n"); break;
            case 0x14: printf("INC D\n"); break;
            case 0x15: printf("DEC D\n"); break;
            case 0x16: printf("LD D,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x17: printf("RLA\n"); break;
            case 0x18: printf("JR (%x)\n", B1_VAL); B1_MOV; break;
            case 0x19: printf("ADD HL,DE\n"); break;
            case 0x1a: printf("LD A,DE\n"); break;
            case 0x1b: printf("DEC DE\n"); break;
            case 0x1c: printf("INC E\n"); break;
            case 0x1d: printf("DEC E\n"); break;
            case 0x1e: printf("LD E,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x1f: printf("RRA\n"); break;

            //0x20 - 0x2f
            case 0x20: printf("JR NZ,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x21: printf("LD HL,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0x22: printf("LD HL+,A\n"); break;
            case 0x23: printf("INC HL\n"); break;
            case 0x24: printf("INC H\n"); break;
            case 0x25: printf("DEC H\n"); break;
            case 0x26: printf("LD H,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x27: printf("DAA\n"); break;
            case 0x28: printf("JR Z,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x29: printf("ADD HL,HL\n"); break;
            case 0x2a: printf("LD A,HL+\n"); break;
            case 0x2b: printf("DEC HL\n"); break;
            case 0x2c: printf("INC L\n"); break;
            case 0x2d: printf("DEC L\n"); break;
            case 0x2e: printf("LD L,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x2f: printf("CPL\n"); break;

            //0x30 - 0x3f
            case 0x30: printf("JR NC,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x31: printf("LD SP,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0x32: printf("LD HL-,A\n"); break;
            case 0x33: printf("INC SP\n"); break;
            case 0x34: printf("INC HL\n"); break;
            case 0x35: printf("DEC HL\n"); break;
            case 0x36: printf("LD HL,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x37: printf("SCF\n"); break;
            case 0x38: printf("JR C,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x39: printf("ADD HL,SP\n"); break;
            case 0x3a: printf("LD A,HL-\n"); break;
            case 0x3b: printf("DEC SP\n"); break;
            case 0x3c: printf("INC A\n"); break;
            case 0x3d: printf("DEC A\n"); break;
            case 0x3e: printf("LD A,(%x)\n", B1_VAL); B1_MOV; break;
            case 0x3f: printf("CCF\n"); break;

            //0x40 - 0x4f
            case 0x40: printf("LD B,B\n"); break;
            case 0x41: printf("LD B,C\n"); break;
            case 0x42: printf("LD B,D\n"); break;
            case 0x43: printf("LD B,E\n"); break;
            case 0x44: printf("LD B,H\n"); break;
            case 0x45: printf("LD B,L\n"); break;
            case 0x46: printf("LD B,HL\n"); break;
            case 0x47: printf("LD B,A\n"); break;

            case 0x48: printf("LD C,B\n"); break;
            case 0x49: printf("LD C,C\n"); break;
            case 0x4a: printf("LD C,D\n"); break;
            case 0x4b: printf("LD C,E\n"); break;
            case 0x4c: printf("LD C,H\n"); break;
            case 0x4d: printf("LD C,L\n"); break;
            case 0x4e: printf("LD C,HL\n"); break;
            case 0x4f: printf("LD C,A\n"); break;

            //0x50 - 0x5f
            case 0x50: printf("LD D,B\n"); break;
            case 0x51: printf("LD D,C\n"); break;
            case 0x52: printf("LD D,D\n"); break;
            case 0x53: printf("LD D,E\n"); break;
            case 0x54: printf("LD D,H\n"); break;
            case 0x55: printf("LD D,L\n"); break;
            case 0x56: printf("LD D,HL\n"); break;
            case 0x57: printf("LD D,A\n"); break;

            case 0x58: printf("LD E,B\n"); break;
            case 0x59: printf("LD E,C\n"); break;
            case 0x5a: printf("LD E,D\n"); break;
            case 0x5b: printf("LD E,E\n"); break;
            case 0x5c: printf("LD E,H\n"); break;
            case 0x5d: printf("LD E,L\n"); break;
            case 0x5e: printf("LD E,HL\n"); break;
            case 0x5f: printf("LD E,A\n"); break;

            //0x60 - 0x6f
            case 0x60: printf("LD H,B\n"); break;
            case 0x61: printf("LD H,C\n"); break;
            case 0x62: printf("LD H,D\n"); break;
            case 0x63: printf("LD H,E\n"); break;
            case 0x64: printf("LD H,H\n"); break;
            case 0x65: printf("LD H,L\n"); break;
            case 0x66: printf("LD H,HL\n"); break;
            case 0x67: printf("LD H,A\n"); break;

            case 0x68: printf("LD L,B\n"); break;
            case 0x69: printf("LD L,C\n"); break;
            case 0x6a: printf("LD L,D\n"); break;
            case 0x6b: printf("LD L,E\n"); break;
            case 0x6c: printf("LD L,H\n"); break;
            case 0x6d: printf("LD L,L\n"); break;
            case 0x6e: printf("LD L,HL\n"); break;
            case 0x6f: printf("LD L,A\n"); break;

            //0x70 - 0x7f
            case 0x70: printf("LD HL,B\n"); break;
            case 0x71: printf("LD HL,C\n"); break;
            case 0x72: printf("LD HL,D\n"); break;
            case 0x73: printf("LD HL,E\n"); break;
            case 0x74: printf("LD HL,H\n"); break;
            case 0x75: printf("LD HL,L\n"); break;
            case 0x76: printf("HALT\n"); break;
            case 0x77: printf("LD H,A\n"); break;

            case 0x78: printf("LD A,B\n"); break;
            case 0x79: printf("LD A,C\n"); break;
            case 0x7a: printf("LD A,D\n"); break;
            case 0x7b: printf("LD A,E\n"); break;
            case 0x7c: printf("LD A,H\n"); break;
            case 0x7d: printf("LD A,L\n"); break;
            case 0x7e: printf("LD A,HL\n"); break;
            case 0x7f: printf("LD A,A\n"); break;

            //0x80 - 0x8f
            case 0x80: printf("ADD A,B\n"); break;
            case 0x81: printf("ADD A,C\n"); break;
            case 0x82: printf("ADD A,D\n"); break;
            case 0x83: printf("ADD A,E\n"); break;
            case 0x84: printf("ADD A,H\n"); break;
            case 0x85: printf("ADD A,L\n"); break;
            case 0x86: printf("ADD A,HL\n"); break;
            case 0x87: printf("ADD A,A\n"); break;

            case 0x88: printf("ADC A,B\n"); break;
            case 0x89: printf("ADC A,C\n"); break;
            case 0x8a: printf("ADC A,D\n"); break;
            case 0x8b: printf("ADC A,E\n"); break;
            case 0x8c: printf("ADC A,H\n"); break;
            case 0x8d: printf("ADC A,L\n"); break;
            case 0x8e: printf("ADC A,HL\n"); break;
            case 0x8f: printf("ADC A,A\n"); break;

            //0x90 - 0x9f
            case 0x90: printf("SUB A,B\n"); break;
            case 0x91: printf("SUB A,C\n"); break;
            case 0x92: printf("SUB A,D\n"); break;
            case 0x93: printf("SUB A,E\n"); break;
            case 0x94: printf("SUB A,H\n"); break;
            case 0x95: printf("SUB A,L\n"); break;
            case 0x96: printf("SUB A,HL\n"); break;
            case 0x97: printf("SUB A,A\n"); break;

            case 0x98: printf("SBC A,B\n"); break;
            case 0x99: printf("SBC A,C\n"); break;
            case 0x9a: printf("SBC A,D\n"); break;
            case 0x9b: printf("SBC A,E\n"); break;
            case 0x9c: printf("SBC A,H\n"); break;
            case 0x9d: printf("SBC A,L\n"); break;
            case 0x9e: printf("SBC A,HL\n"); break;
            case 0x9f: printf("SBC A,A\n"); break;

            //0xa0 - 0xaf
            case 0xa0: printf("AND B\n"); break;
            case 0xa1: printf("AND C\n"); break;
            case 0xa2: printf("AND D\n"); break;
            case 0xa3: printf("AND E\n"); break;
            case 0xa4: printf("AND H\n"); break;
            case 0xa5: printf("AND L\n"); break;
            case 0xa6: printf("AND HL\n"); break;
            case 0xa7: printf("AND A\n"); break;

            case 0xa8: printf("XOR B\n"); break;
            case 0xa9: printf("XOR C\n"); break;
            case 0xaa: printf("XOR D\n"); break;
            case 0xab: printf("XOR E\n"); break;
            case 0xac: printf("XOR H\n"); break;
            case 0xad: printf("XOR L\n"); break;
            case 0xae: printf("XOR HL\n"); break;
            case 0xaf: printf("XOR A\n"); break;

            //0xb0 - 0xbf
            case 0xb0: printf("OR B\n"); break;
            case 0xb1: printf("OR C\n"); break;
            case 0xb2: printf("OR D\n"); break;
            case 0xb3: printf("OR E\n"); break;
            case 0xb4: printf("OR H\n"); break;
            case 0xb5: printf("OR L\n"); break;
            case 0xb6: printf("OR HL\n"); break;
            case 0xb7: printf("OR A\n"); break;

            case 0xb8: printf("CP B\n"); break;
            case 0xb9: printf("CP C\n"); break;
            case 0xba: printf("CP D\n"); break;
            case 0xbb: printf("CP E\n"); break;
            case 0xbc: printf("CP H\n"); break;
            case 0xbd: printf("CP L\n"); break;
            case 0xbe: printf("CP HL\n"); break;
            case 0xbf: printf("CP A\n"); break;

            //0xc0 - 0xcf
            case 0xc0: printf("RET NZ\n"); break;
            case 0xc1: printf("POP BC\n"); break;
            case 0xc2: printf("JP NZ,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xc3: printf("JP (%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xc4: printf("CALL NZ,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xc5: printf("PUSH BC\n"); break;
            case 0xc6: printf("ADD A,(%x)\n", B1_VAL); B1_MOV; break;
            case 0xc7: printf("RST 00H\n"); break;
            case 0xc8: printf("RET Z\n"); break;
            case 0xc9: printf("RET\n"); break;
            case 0xca: printf("JP Z,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xcb: dasm_prefix_0xCB(buffer, &byte_index); break;
            case 0xcc: printf("CALL Z,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xcd: printf("CALL (%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xce: printf("ADC A,(%x)\n", B1_VAL); B1_MOV; break;
            case 0xcf: printf("RST 08H\n"); break;

            //0xd0 - 0xdf
            case 0xd0: printf("RET NC\n"); break;
            case 0xd1: printf("POP DE\n"); break;
            case 0xd2: printf("JP NC,(%x %x)\n", B2_VAL); B2_MOV; break;

            case 0xd4: printf("CALL NC,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xd5: printf("PUSH DE\n"); break;
            case 0xd6: printf("SUB (%x)\n", B1_VAL); B1_MOV; break;
            case 0xd7: printf("RST 10H\n"); break;
            case 0xd8: printf("RET C\n"); break;
            case 0xd9: printf("RETI\n"); break;
            case 0xda: printf("JP C,(%x %x)\n", B2_VAL); B2_MOV; break;

            case 0xdc: printf("CALL C,(%x %x)\n", B2_VAL); B2_MOV; break;

            case 0xde: printf("SBC A,(%x)\n", B1_VAL); B1_MOV; break;
            case 0xdf: printf("RST 18H\n"); break;

            //0xe0 - 0xef
            case 0xe0: printf("LDH (%x),A\n", B1_VAL); B1_MOV; break;
            case 0xe1: printf("POP HL\n"); break;
            case 0xe2: printf("LD C,A\n"); B1_MOV; break;

            case 0xe5: printf("PUSH HL\n"); break;
            case 0xe6: printf("AND (%x)\n", B1_VAL); B1_MOV; break;
            case 0xe7: printf("RST 20H\n"); break;
            case 0xe8: printf("ADD SP,(%x)\n",B1_VAL); B1_MOV; break;
            case 0xe9: printf("JP HL\n"); break;
            case 0xea: printf("LD (%x %x),A\n", B2_VAL); B2_MOV; break;

            case 0xee: printf("XOR (%x)\n", B1_VAL); B1_MOV; break;
            case 0xef: printf("RST 28H\n"); break;

            //0xf0 - 0xff
            case 0xf0: printf("LDH A,(%x)\n", B1_VAL); B1_MOV; break;
            case 0xf1: printf("POP AF\n"); break;
            case 0xf2: printf("LD A,C\n"); B1_MOV; break;
            case 0xf3: printf("DI\n"); B1_MOV; break;

            case 0xf5: printf("PUSH AF\n"); break;
            case 0xf6: printf("OR (%x)\n", B1_VAL); B1_MOV; break;
            case 0xf7: printf("RST 30H\n"); break;
            case 0xf8: printf("LD HL,SP+(%x)\n",B1_VAL); B1_MOV; break;
            case 0xf9: printf("LD SP,HL\n"); break;
            case 0xfa: printf("LD A,(%x %x)\n", B2_VAL); B2_MOV; break;
            case 0xfb: printf("EI\n"); break;

            case 0xfe: printf("CP (%x)\n", B1_VAL); B1_MOV; break;
            case 0xff: printf("RST 38H\n"); break;

            default: printf("Unrecognised opcode: (%x) at (%lx)\n", buffer[byte_index], byte_index); break;
        }

        ++byte_index;
    }

}

void dasm_prefix_0xCB(uint8_t* buffer, ssize_t* byte_index_ptr) {
    // byte_index_ptr is still pointing at 0xCB prefix in buffer,
    // we need to move it to the next byte.
    // All 0xCB prefix commands are two byte commands,
    // thus there will be one byte remaining here.
    ++(*byte_index_ptr);
    switch(buffer[*byte_index_ptr]) {
        //0x00 - 0x0f
        case 0x00: printf("RLC B\n"); break;
        case 0x01: printf("RLC C\n"); break;
        case 0x02: printf("RLC D\n"); break;
        case 0x03: printf("RLC E\n"); break;
        case 0x04: printf("RLC H\n"); break;
        case 0x05: printf("RLC L\n"); break;
        case 0x06: printf("RLC HL\n"); break;
        case 0x07: printf("RLC A\n"); break;

        case 0x08: printf("RRC B\n"); break;
        case 0x09: printf("RRC C\n"); break;
        case 0x0a: printf("RRC D\n"); break;
        case 0x0b: printf("RRC E\n"); break;
        case 0x0c: printf("RRC H\n"); break;
        case 0x0d: printf("RRC L\n"); break;
        case 0x0e: printf("RRC HL\n"); break;
        case 0x0f: printf("RRC A\n"); break;

        //0x10 - 0x1f
        case 0x10: printf("RL B\n"); break;
        case 0x11: printf("RL C\n"); break;
        case 0x12: printf("RL D\n"); break;
        case 0x13: printf("RL E\n"); break;
        case 0x14: printf("RL H\n"); break;
        case 0x15: printf("RL L\n"); break;
        case 0x16: printf("RL HL\n"); break;
        case 0x17: printf("RL A\n"); break;

        case 0x18: printf("RR B\n"); break;
        case 0x19: printf("RR C\n"); break;
        case 0x1a: printf("RR D\n"); break;
        case 0x1b: printf("RR E\n"); break;
        case 0x1c: printf("RR H\n"); break;
        case 0x1d: printf("RR L\n"); break;
        case 0x1e: printf("RR HL\n"); break;
        case 0x1f: printf("RR A\n"); break;

        //0x20 - 0x2f
        case 0x20: printf("SLA B\n"); break;
        case 0x21: printf("SLA C\n"); break;
        case 0x22: printf("SLA D\n"); break;
        case 0x23: printf("SLA E\n"); break;
        case 0x24: printf("SLA H\n"); break;
        case 0x25: printf("SLA L\n"); break;
        case 0x26: printf("SLA HL\n"); break;
        case 0x27: printf("SLA A\n"); break;

        case 0x28: printf("SRA B\n"); break;
        case 0x29: printf("SRA C\n"); break;
        case 0x2a: printf("SRA D\n"); break;
        case 0x2b: printf("SRA E\n"); break;
        case 0x2c: printf("SRA H\n"); break;
        case 0x2d: printf("SRA L\n"); break;
        case 0x2e: printf("SRA HL\n"); break;
        case 0x2f: printf("SRA A\n"); break;

        //0x30 - 0x3f
        case 0x30: printf("SWAP B\n"); break;
        case 0x31: printf("SWAP C\n"); break;
        case 0x32: printf("SWAP D\n"); break;
        case 0x33: printf("SWAP E\n"); break;
        case 0x34: printf("SWAP H\n"); break;
        case 0x35: printf("SWAP L\n"); break;
        case 0x36: printf("SWAP HL\n"); break;
        case 0x37: printf("SWAP A\n"); break;

        case 0x38: printf("SRL B\n"); break;
        case 0x39: printf("SRL C\n"); break;
        case 0x3a: printf("SRL D\n"); break;
        case 0x3b: printf("SRL E\n"); break;
        case 0x3c: printf("SRL H\n"); break;
        case 0x3d: printf("SRL L\n"); break;
        case 0x3e: printf("SRL HL\n"); break;
        case 0x3f: printf("SRL A\n"); break;

        //0x40 - 0x4f
        case 0x40: printf("BIT 0,B\n"); break;
        case 0x41: printf("BIT 0,C\n"); break;
        case 0x42: printf("BIT 0,D\n"); break;
        case 0x43: printf("BIT 0,E\n"); break;
        case 0x44: printf("BIT 0,H\n"); break;
        case 0x45: printf("BIT 0,L\n"); break;
        case 0x46: printf("BIT 0,HL\n"); break;
        case 0x47: printf("BIT 0,A\n"); break;

        case 0x48: printf("BIT 1,B\n"); break;
        case 0x49: printf("BIT 1,C\n"); break;
        case 0x4a: printf("BIT 1,D\n"); break;
        case 0x4b: printf("BIT 1,E\n"); break;
        case 0x4c: printf("BIT 1,H\n"); break;
        case 0x4d: printf("BIT 1,L\n"); break;
        case 0x4e: printf("BIT 1,HL\n"); break;
        case 0x4f: printf("BIT 1,A\n"); break;

        //0x50 - 0x5f
        case 0x50: printf("BIT 2,B\n"); break;
        case 0x51: printf("BIT 2,C\n"); break;
        case 0x52: printf("BIT 2,D\n"); break;
        case 0x53: printf("BIT 2,E\n"); break;
        case 0x54: printf("BIT 2,H\n"); break;
        case 0x55: printf("BIT 2,L\n"); break;
        case 0x56: printf("BIT 2,HL\n"); break;
        case 0x57: printf("BIT 2,A\n"); break;

        case 0x58: printf("BIT 3,B\n"); break;
        case 0x59: printf("BIT 3,C\n"); break;
        case 0x5a: printf("BIT 3,D\n"); break;
        case 0x5b: printf("BIT 3,E\n"); break;
        case 0x5c: printf("BIT 3,H\n"); break;
        case 0x5d: printf("BIT 3,L\n"); break;
        case 0x5e: printf("BIT 3,HL\n"); break;
        case 0x5f: printf("BIT 3,A\n"); break;

        //0x60 - 0x6f
        case 0x60: printf("BIT 4,B\n"); break;
        case 0x61: printf("BIT 4,C\n"); break;
        case 0x62: printf("BIT 4,D\n"); break;
        case 0x63: printf("BIT 4,E\n"); break;
        case 0x64: printf("BIT 4,H\n"); break;
        case 0x65: printf("BIT 4,L\n"); break;
        case 0x66: printf("BIT 4,HL\n"); break;
        case 0x67: printf("BIT 4,A\n"); break;

        case 0x68: printf("BIT 5,B\n"); break;
        case 0x69: printf("BIT 5,C\n"); break;
        case 0x6a: printf("BIT 5,D\n"); break;
        case 0x6b: printf("BIT 5,E\n"); break;
        case 0x6c: printf("BIT 5,H\n"); break;
        case 0x6d: printf("BIT 5,L\n"); break;
        case 0x6e: printf("BIT 5,HL\n"); break;
        case 0x6f: printf("BIT 5,A\n"); break;

        //0x70 - 0x7f
        case 0x70: printf("BIT 6,B\n"); break;
        case 0x71: printf("BIT 6,C\n"); break;
        case 0x72: printf("BIT 6,D\n"); break;
        case 0x73: printf("BIT 6,E\n"); break;
        case 0x74: printf("BIT 6,H\n"); break;
        case 0x75: printf("BIT 6,L\n"); break;
        case 0x76: printf("BIT 6,HL\n"); break;
        case 0x77: printf("BIT 6,A\n"); break;

        case 0x78: printf("BIT 7,B\n"); break;
        case 0x79: printf("BIT 7,C\n"); break;
        case 0x7a: printf("BIT 7,D\n"); break;
        case 0x7b: printf("BIT 7,E\n"); break;
        case 0x7c: printf("BIT 7,H\n"); break;
        case 0x7d: printf("BIT 7,L\n"); break;
        case 0x7e: printf("BIT 7,HL\n"); break;
        case 0x7f: printf("BIT 7,A\n"); break;

        //0x80 - 0x8f
        case 0x80: printf("RES 0,B\n"); break;
        case 0x81: printf("RES 0,C\n"); break;
        case 0x82: printf("RES 0,D\n"); break;
        case 0x83: printf("RES 0,E\n"); break;
        case 0x84: printf("RES 0,H\n"); break;
        case 0x85: printf("RES 0,L\n"); break;
        case 0x86: printf("RES 0,HL\n"); break;
        case 0x87: printf("RES 0,A\n"); break;

        case 0x88: printf("RES 1,B\n"); break;
        case 0x89: printf("RES 1,C\n"); break;
        case 0x8a: printf("RES 1,D\n"); break;
        case 0x8b: printf("RES 1,E\n"); break;
        case 0x8c: printf("RES 1,H\n"); break;
        case 0x8d: printf("RES 1,L\n"); break;
        case 0x8e: printf("RES 1,HL\n"); break;
        case 0x8f: printf("RES 1,A\n"); break;

        //0x90 - 0x9f
        case 0x90: printf("RES 2,B\n"); break;
        case 0x91: printf("RES 2,C\n"); break;
        case 0x92: printf("RES 2,D\n"); break;
        case 0x93: printf("RES 2,E\n"); break;
        case 0x94: printf("RES 2,H\n"); break;
        case 0x95: printf("RES 2,L\n"); break;
        case 0x96: printf("RES 2,HL\n"); break;
        case 0x97: printf("RES 2,A\n"); break;

        case 0x98: printf("RES 3,B\n"); break;
        case 0x99: printf("RES 3,C\n"); break;
        case 0x9a: printf("RES 3,D\n"); break;
        case 0x9b: printf("RES 3,E\n"); break;
        case 0x9c: printf("RES 3,H\n"); break;
        case 0x9d: printf("RES 3,L\n"); break;
        case 0x9e: printf("RES 3,HL\n"); break;
        case 0x9f: printf("RES 3,A\n"); break;

        //0xa0 - 0xaf
        case 0xa0: printf("RES 4,B\n"); break;
        case 0xa1: printf("RES 4,C\n"); break;
        case 0xa2: printf("RES 4,D\n"); break;
        case 0xa3: printf("RES 4,E\n"); break;
        case 0xa4: printf("RES 4,H\n"); break;
        case 0xa5: printf("RES 4,L\n"); break;
        case 0xa6: printf("RES 4,HL\n"); break;
        case 0xa7: printf("RES 4,A\n"); break;

        case 0xa8: printf("RES 5,B\n"); break;
        case 0xa9: printf("RES 5,C\n"); break;
        case 0xaa: printf("RES 5,D\n"); break;
        case 0xab: printf("RES 5,E\n"); break;
        case 0xac: printf("RES 5,H\n"); break;
        case 0xad: printf("RES 5,L\n"); break;
        case 0xae: printf("RES 5,HL\n"); break;
        case 0xaf: printf("RES 5,A\n"); break;

        //0xb0 - 0xbf
        case 0xb0: printf("RES 6,B\n"); break;
        case 0xb1: printf("RES 6,C\n"); break;
        case 0xb2: printf("RES 6,D\n"); break;
        case 0xb3: printf("RES 6,E\n"); break;
        case 0xb4: printf("RES 6,H\n"); break;
        case 0xb5: printf("RES 6,L\n"); break;
        case 0xb6: printf("RES 6,HL\n"); break;
        case 0xb7: printf("RES 6,A\n"); break;

        case 0xb8: printf("RES 7,B\n"); break;
        case 0xb9: printf("RES 7,C\n"); break;
        case 0xba: printf("RES 7,D\n"); break;
        case 0xbb: printf("RES 7,E\n"); break;
        case 0xbc: printf("RES 7,H\n"); break;
        case 0xbd: printf("RES 7,L\n"); break;
        case 0xbe: printf("RES 7,HL\n"); break;
        case 0xbf: printf("RES 7,A\n"); break;

        //0xc0 - 0xcf
        case 0xc0: printf("SET 0,B\n"); break;
        case 0xc1: printf("SET 0,C\n"); break;
        case 0xc2: printf("SET 0,D\n"); break;
        case 0xc3: printf("SET 0,E\n"); break;
        case 0xc4: printf("SET 0,H\n"); break;
        case 0xc5: printf("SET 0,L\n"); break;
        case 0xc6: printf("SET 0,HL\n"); break;
        case 0xc7: printf("SET 0,A\n"); break;

        case 0xc8: printf("SET 1,B\n"); break;
        case 0xc9: printf("SET 1,C\n"); break;
        case 0xca: printf("SET 1,D\n"); break;
        case 0xcb: printf("SET 1,E\n"); break;
        case 0xcc: printf("SET 1,H\n"); break;
        case 0xcd: printf("SET 1,L\n"); break;
        case 0xce: printf("SET 1,HL\n"); break;
        case 0xcf: printf("SET 1,A\n"); break;

        //0xd0 - 0xdf
        case 0xd0: printf("SET 2,B\n"); break;
        case 0xd1: printf("SET 2,C\n"); break;
        case 0xd2: printf("SET 2,D\n"); break;
        case 0xd3: printf("SET 2,E\n"); break;
        case 0xd4: printf("SET 2,H\n"); break;
        case 0xd5: printf("SET 2,L\n"); break;
        case 0xd6: printf("SET 2,HL\n"); break;
        case 0xd7: printf("SET 2,A\n"); break;

        case 0xd8: printf("SET 3,B\n"); break;
        case 0xd9: printf("SET 3,C\n"); break;
        case 0xda: printf("SET 3,D\n"); break;
        case 0xdb: printf("SET 3,E\n"); break;
        case 0xdc: printf("SET 3,H\n"); break;
        case 0xdd: printf("SET 3,L\n"); break;
        case 0xde: printf("SET 3,HL\n"); break;
        case 0xdf: printf("SET 3,A\n"); break;

        //0xe0 - 0xef
        case 0xe0: printf("SET 4,B\n"); break;
        case 0xe1: printf("SET 4,C\n"); break;
        case 0xe2: printf("SET 4,D\n"); break;
        case 0xe3: printf("SET 4,E\n"); break;
        case 0xe4: printf("SET 4,H\n"); break;
        case 0xe5: printf("SET 4,L\n"); break;
        case 0xe6: printf("SET 4,HL\n"); break;
        case 0xe7: printf("SET 4,A\n"); break;

        case 0xe8: printf("SET 5,B\n"); break;
        case 0xe9: printf("SET 5,C\n"); break;
        case 0xea: printf("SET 5,D\n"); break;
        case 0xeb: printf("SET 5,E\n"); break;
        case 0xec: printf("SET 5,H\n"); break;
        case 0xed: printf("SET 5,L\n"); break;
        case 0xee: printf("SET 5,HL\n"); break;
        case 0xef: printf("SET 5,A\n"); break;

        //0xf0 - 0xff
        case 0xf0: printf("SET 6,B\n"); break;
        case 0xf1: printf("SET 6,C\n"); break;
        case 0xf2: printf("SET 6,D\n"); break;
        case 0xf3: printf("SET 6,E\n"); break;
        case 0xf4: printf("SET 6,H\n"); break;
        case 0xf5: printf("SET 6,L\n"); break;
        case 0xf6: printf("SET 6,HL\n"); break;
        case 0xf7: printf("SET 6,A\n"); break;

        case 0xf8: printf("SET 7,B\n"); break;
        case 0xf9: printf("SET 7,C\n"); break;
        case 0xfa: printf("SET 7,D\n"); break;
        case 0xfb: printf("SET 7,E\n"); break;
        case 0xfc: printf("SET 7,H\n"); break;
        case 0xfd: printf("SET 7,L\n"); break;
        case 0xfe: printf("SET 7,HL\n"); break;
        case 0xff: printf("SET 7,A\n"); break;
    }
}
