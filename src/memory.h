#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdio.h>
#include <stdint.h>

#include "byte.h"

#define VRAM_BEGIN 0x8000
#define VRAM_END 0xBFFF
#define WRAM_BEGIN 0xC000
#define WRAM_END 0xDFFF
#define OAM_BEGIN 0xFE00
#define OAM_END 0xFE9F
#define HRAM_BEGIN 0xFF00
#define HRAM_END 0xFFFF

typedef struct Memory {

    uint8_t* vram;
    uint8_t* wram;
    uint8_t* oam;
    uint8_t* hram;
} Memory;

typedef enum MemoryRegister {
    MREG_P1 = 0x00,
    MREG_SB = 0x01,
    MREG_SC = 0x02,
    MREG_DIV = 0x04,
    MREG_TIMA = 0x05,
    MREG_TMA = 0x06,
    MREG_TAC = 0x07,

    MREG_IF = 0x0f,

    MREG_NR10 = 0x10,
    MREG_NR11 = 0x11,
    MREG_NR12 = 0x12,
    MREG_NR13 = 0x13,
    MREG_NR14 = 0x14,
    MREG_NR21 = 0x16,
    MREG_NR22 = 0x17,
    MREG_NR23 = 0x18,
    MREG_NR24 = 0x19,
    MREG_NR30 = 0x1a,
    MREG_NR31 = 0x1b,
    MREG_NR32 = 0x1c,
    MREG_NR33 = 0x1d,
    MREG_NR34 = 0x1e,
    MREG_NR41 = 0x20,
    MREG_NR42 = 0x21,
    MREG_NR43 = 0x22,
    MREG_NR44 = 0x23,
    MREG_NR50 = 0x24,
    MREG_NR51 = 0x25,
    MREG_NR52 = 0x26,

    MREG_LCDC = 0x40,
    MREG_STAT = 0x41,
    MREG_SCY = 0x42,
    MREG_SCX = 0x43,
    MREG_LY = 0x44,
    MREG_LYC = 0x45,
    MREG_DMA = 0x46,
    MREG_BGP = 0x47,
    MREG_OBP0 = 0x48,
    MREG_OBP1 = 0x49,
    MREG_WY = 0x4a,
    MREG_WX = 0x4b,

    MREG_KEY1 = 0x4d,
    MREG_VBK = 0x4f,

    MREG_HDMA1 = 0x51,
    MREG_HDMA2 = 0x52,
    MREG_HDMA3 = 0x53,
    MREG_HDMA4 = 0x54,
    MREG_HDMA5 = 0x55,

    MREG_RP = 0x56,

    MREG_BCPS = 0x68,
    MREG_BCPD = 0x69,
    MREG_OCPS = 0x6a,
    MREG_OCPD = 0x6b,

    MREG_OPRI = 0x6c,
    MREG_SVBK = 0x70,

    MREG_IE = 0xff
} MemoryRegister;

uint8_t* access_memory(Memory memory, uint8_t* address);

#endif
