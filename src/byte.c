#include "byte.h"

uint8_t low_nibble(uint8_t byte) {
    return byte & 0x0f;
}

uint8_t high_nibble(uint8_t byte) {
    return byte & 0xf0;
}

uint8_t low_byte(uint16_t twobytes) {
    return twobytes & 0x00ff;
}

uint8_t high_byte(uint16_t twobytes) {
    return (twobytes & 0xff00) >> 8;
}

uint16_t merge_bytes(uint8_t high, uint8_t low) {
    return (high << 8) + low;
}

uint8_t get_bit(uint8_t byte, Bit bit) {
    return (byte & bit);
}

void set_bit(uint8_t* byte_ptr, Bit bit) {
    (*byte_ptr) |= bit;
}

void unset_bit(uint8_t* byte_ptr, Bit bit) {
    (*byte_ptr) &= (~bit);
}

uint16_t ptr_offset(uint16_t greater_ptr, uint16_t lesser_ptr) {
    return greater_ptr - lesser_ptr;
}

uint8_t ptr_in(uint16_t ptr, uint16_t low_addr, uint16_t high_addr) {
    long ptr_long = (long) ptr;
    return (ptr_long >= low_addr) && (ptr_long <= high_addr);
}
