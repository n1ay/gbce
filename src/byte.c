#include "byte.h"

uint8_t low_nibble(uint8_t byte) {
    return byte & 0x0f;
}

uint8_t high_nibble(uint8_t byte) {
    return byte & 0xf0;
}

uint8_t low_byte(uint16_t twobytes) {
    uint8_t* byte_ptr = (uint8_t*) &twobytes;
    return (* byte_ptr);
}

uint8_t high_byte(uint16_t twobytes) {
    uint8_t* byte_ptr = (uint8_t*) &twobytes;
    return (* (byte_ptr + 1));
}

uint8_t get_bit(uint8_t byte, Bit bit) {
    return (byte & bit) != 0;
}

void set_bit(uint8_t* byte_ptr, Bit bit) {
    (*byte_ptr) |= bit;
}

void zero_bit(uint8_t* byte_ptr, Bit bit) {
    (*byte_ptr) &= (~bit);
}
