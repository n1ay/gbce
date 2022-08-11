#include "byte.h"

static void get_bits(uint16_t value, uint16_t* bits);

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

uint8_t get_bit_number(Bit bit) {
    switch(bit) {
        case BIT0:
            return 0;
        case BIT1:
            return 1;
        case BIT2:
            return 2;
        case BIT3:
            return 3;
        case BIT4:
            return 4;
        case BIT5:
            return 5;
        case BIT6:
            return 6;
        case BIT7:
            return 7;
        case BIT8:
            return 8;
        case BIT9:
            return 9;
        case BIT10:
            return 10;
        case BIT11:
            return 11;
        case BIT12:
            return 12;
        case BIT13:
            return 13;
        case BIT14:
            return 14;
        case BIT15:
            return 15;
        default:
            return 0;
    }
}

static void get_bits(uint16_t value, uint16_t* bits) {
    bits[0] = value & BIT0;
    bits[1] = value & BIT1;
    bits[2] = value & BIT2;
    bits[3] = value & BIT3;
    bits[4] = value & BIT4;
    bits[5] = value & BIT5;
    bits[6] = value & BIT6;
    bits[7] = value & BIT7;
    bits[8] = value & BIT8;
    bits[9] = value & BIT9;
    bits[10] = value & BIT10;
    bits[11] = value & BIT11;
    bits[12] = value & BIT12;
    bits[13] = value & BIT13;
    bits[14] = value & BIT14;
    bits[15] = value & BIT15;
}

uint8_t get_8b_half_carry_bit(uint8_t value1, uint8_t value2) {
    return (((value1 & 0x0f) + (value2 & 0x0f)) & 0x10) == 0x10;
}

uint8_t get_8b_carry_bit(uint8_t value1, uint8_t value2) {
    return ((((uint16_t) value1) + ((uint16_t) value2)) & 0x0100) == 0x0100;
}

uint8_t get_16b_half_carry_bit(uint16_t value1, uint16_t value2) {
    return (((value1 & 0x0fff) + (value2 & 0x0fff)) & 0x1000) == 0x1000;
}

uint8_t get_16b_carry_bit(uint16_t value1, uint16_t value2) {
    return ((((uint32_t) value1) + ((uint32_t) value2)) & 0x10000) == 0x10000;
}

uint8_t get_8b_half_borrow_bit(uint8_t minuend, uint8_t subtrahend) {
    return (minuend & 0x0f) < (subtrahend & 0x0f);
}

uint8_t get_8b_borrow_bit(uint8_t minuend, uint8_t subtrahend) {
    return ((uint8_t) minuend) < ((uint8_t) subtrahend);
}

