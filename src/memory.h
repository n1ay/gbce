#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>
typedef struct Memory {

    uint8_t* vram;
    uint8_t* wram;
    uint8_t* oam;
    uint8_t* hram;
} Memory;

typedef enum MemoryRegister {
    P1 = 0x00,
    SB = 0x01,
    SC = 0x02,
    DIV = 0x04,
    TIMA = 0x05,
    TMA = 0x06,
    TAC = 0x07,

    NR10 = 0x10,
    NR11 = 0x11,
    NR12 = 0x12,
    NR13 = 0x13,
    NR14 = 0x14,
    NR21 = 0x16,
    NR22 = 0x17,
    NR23 = 0x18,
    NR24 = 0x19,
    NR30 = 0x1a,
    NR31 = 0x1b,
    NR32 = 0x1c,
    NR33 = 0x1d,
    NR34 = 0x1e,
    NR41 = 0x20,
    NR42 = 0x21,
    NR43 = 0x22,
    NR44 = 0x23,
    NR50 = 0x24,
    NR51 = 0x25,
    NR52 = 0x26,

    IF = 0x0f,

    LCDC = 0x40,
    STAT = 0x41,
    SCY = 0x42,
    SCX = 0x43,
    LY = 0x44,
    LYC = 0x45,
    DMA = 0x46,
    BGP = 0x47,
    OBP0 = 0x48,
    OBP1 = 0x49,
    WY = 0x4a,
    WX = 0x4b,

    KEY1 = 0x4d,
    VBK = 0x4f,

    HDMA1 = 0x51,
    HDMA3 = 0x53,
    HDMA5 = 0x55,

    RP = 0x56,

    BCPS = 0x68,
    BGPI = 0x68,
    BCPD = 0x69,
    BGPD = 0x69,
    OCPS = 0x6a,
    OBPI = 0x6a,
    OCPD = 0x6b,
    OBPD = 0x6b,

    OPRI = 0x6c,
    SVBK = 0x70,

    IE = 0xff
} MemoryRegister;

#endif
