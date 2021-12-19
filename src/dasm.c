#include "dasm.h"

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
