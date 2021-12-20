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

void disassembly(int fd) {
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

            default: printf("Unrecognised opcode: (%x) at (%lx)\n", buffer[byte_index], byte_index); break;
        }

        ++byte_index;
    }
}
