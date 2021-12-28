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

uint16_t merge_bytes(uint8_t high, uint8_t low) {
    return (high << 8) + low;
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

uint16_t ptr_offset(uint8_t* greater_ptr, uint16_t lesser_ptr) {
    return (long) greater_ptr - lesser_ptr;
}

uint8_t ptr_in(uint8_t* ptr, uint16_t low_addr, uint16_t high_addr) {
    long ptr_long = (long) ptr;
    return (ptr_long >= low_addr) && (ptr_long <= high_addr);
}
