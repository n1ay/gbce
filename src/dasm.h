#ifndef _DASM_H_
#define _DASM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE (16 * 1024 * 1024)

void disassembly(int fd);

#endif
