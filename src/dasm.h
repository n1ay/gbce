#ifndef _DASM_H_
#define _DASM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE (16 * 1024 * 1024)

#define B1_VAL buffer[byte_index + 1]
#define B1_MOV byte_index += 1
#define B2_VAL buffer[byte_index + 1], buffer[byte_index + 2]
#define B2_MOV byte_index += 2

void hexdump(int fd);
void disassembly(int fd);

#endif
