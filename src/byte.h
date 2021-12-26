#ifndef _BYTE_H_
#define _BYTE_H_

#include <stdint.h>

typedef enum Bit {
    BIT0 = 0x01,
    BIT1 = 0x02,
    BIT2 = 0x04,
    BIT3 = 0x08,
    BIT4 = 0x10,
    BIT5 = 0x20,
    BIT6 = 0x40,
    BIT7 = 0x80
} Bit;

uint8_t low_nibble(uint8_t byte);
uint8_t high_nibble(uint8_t byte);
uint8_t low_byte(uint16_t twobytes);
uint8_t high_byte(uint16_t twobytes);
uint8_t get_bit(uint8_t byte, Bit bit);
void set_bit(uint8_t* byte_ptr, Bit bit);
void zero_bit(uint8_t* byte_ptr, Bit bit);
#endif
