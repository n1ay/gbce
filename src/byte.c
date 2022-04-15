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

uint8_t add_get_carry_bit(uint16_t value1, uint16_t value2, Bit bit) {
    uint16_t value1_bits[16];
    uint16_t value2_bits[16];
    get_bits(value1, value1_bits);
    get_bits(value2, value2_bits);

    // 17 bit carry to simplify logic for the 0 bit carry
    uint8_t carried_bits[17] = {[0] = 0};

    for (int i = 0; i < 16; i++) {
        carried_bits[i + 1] = ((value1_bits[i] && value2_bits[i]) || (value1_bits[i] && carried_bits[i]) || (value2_bits[i] && carried_bits[i]));
    }

    return carried_bits[get_bit_number(bit) + 1];
}

uint8_t subtract_get_borrow_bit(uint16_t value1, uint16_t value2, Bit bit) {
    uint16_t result = value1 - value2;
    return add_get_carry_bit(value2, result, bit);
}
