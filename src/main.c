#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "dasm.h"

#define EXIT_INSUFFICIENT_ARGS 1
#define EXIT_TOO_MANY_ARGS 2
#define EXIT_FILE_OPEN_ERROR 3

void print_help() {
    printf("Usage:\t./gbce [FILE]\n");
}

int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "Insufficient number of arguments\n");
        print_help();
        exit(EXIT_INSUFFICIENT_ARGS);
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        print_help();
        exit(EXIT_TOO_MANY_ARGS);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Could not open file: %s", argv[1]);
        exit(EXIT_FILE_OPEN_ERROR);
    }

    disassembly(fd);

    close(fd);
    return 0;
}
