#ifndef _BYTE_H_
#define _BYTE_H_

#include <stdint.h>

typedef enum Bit {
    BIT0 = 0x0001,
    BIT1 = 0x0002,
    BIT2 = 0x0004,
    BIT3 = 0x0008,
    BIT4 = 0x0010,
    BIT5 = 0x0020,
    BIT6 = 0x0040,
    BIT7 = 0x0080,
    BIT8 = 0x0100,
    BIT9 = 0x0200,
    BIT10 = 0x0400,
    BIT11 = 0x0800,
    BIT12 = 0x1000,
    BIT13 = 0x2000,
    BIT14 = 0x4000,
    BIT15 = 0x8000,
} Bit;

uint8_t low_nibble(uint8_t byte);
uint8_t high_nibble(uint8_t byte);
uint8_t low_byte(uint16_t twobytes);
uint8_t high_byte(uint16_t twobytes);
uint16_t merge_bytes(uint8_t low, uint8_t high);
uint8_t get_bit(uint8_t byte, Bit bit);
void set_bit(uint8_t* byte_ptr, Bit bit);
void unset_bit(uint8_t* byte_ptr, Bit bit);
uint16_t ptr_offset(uint16_t greater_ptr, uint16_t lesser_ptr);
uint8_t ptr_in(uint16_t ptr, uint16_t low_addr, uint16_t high_addr);
uint8_t get_bit_number(Bit bit);
uint8_t add_get_carry_bit(uint16_t value1, uint16_t value2, Bit bit);
uint8_t subtract_get_borrow_bit(uint16_t value1, uint16_t value2, Bit bit);
#endif
