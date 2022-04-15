#include "byte.h"

static void get_bits(uint8_t byte, uint8_t* bits);

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
        default:
            return 0;
    }
}

static void get_bits(uint8_t byte, uint8_t* bits) {
    bits[0] = byte & BIT0;
    bits[1] = byte & BIT1;
    bits[2] = byte & BIT2;
    bits[3] = byte & BIT3;
    bits[4] = byte & BIT4;
    bits[5] = byte & BIT5;
    bits[6] = byte & BIT6;
    bits[7] = byte & BIT7;
}

uint8_t add_get_carry_bit(uint8_t byte1, uint8_t byte2, Bit bit) {
    uint8_t byte1_bits[8];
    uint8_t byte2_bits[8];
    get_bits(byte1, byte1_bits);
    get_bits(byte2, byte2_bits);

    // 9 bit carry to simplify logic for the 0 bit carry
    uint8_t carried_bits[9] = {[0] = 0};

    for (int i = 0; i < 8; i++) {
        carried_bits[i + 1] = ((byte1_bits[i] && byte2_bits[i]) || (byte1_bits[i] && carried_bits[i]) || (byte2_bits[i] && carried_bits[i]));
    }

    return carried_bits[get_bit_number(bit) + 1];
}
