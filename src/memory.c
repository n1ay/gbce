#include "memory.h"

static void init_memory_registers(Memory* memory);

uint8_t* access_memory(Memory memory, uint16_t address) {
    if (ptr_in(address, VRAM_BEGIN, VRAM_END)) {
        return &(memory.vram[ptr_offset(address, VRAM_BEGIN)]);
    } else if (ptr_in(address, WRAM_BEGIN, WRAM_END)) {
        return &(memory.wram[ptr_offset(address, WRAM_BEGIN)]);
    } else if (ptr_in(address, OAM_BEGIN, OAM_END)) {
        return &(memory.oam[ptr_offset(address, OAM_BEGIN)]);
    } else if (ptr_in(address, HRAM_BEGIN, HRAM_END)) {
        return &(memory.hram[ptr_offset(address, HRAM_BEGIN)]);
    } else {
        fprintf(stderr, "Memory access violation: (%#06x)\n", address);
        return NULL;
    }
}

void init_memory(Memory* memory) {
    memory->vram = (uint8_t*) malloc(VRAM_END - VRAM_BEGIN + 1);
    memory->wram = (uint8_t*) malloc(WRAM_END - WRAM_BEGIN + 1);
    memory->oam = (uint8_t*) malloc(OAM_END - OAM_BEGIN + 1);
    memory->hram = (uint8_t*) malloc(HRAM_END - HRAM_BEGIN + 1);

    memset(memory->vram, 0, VRAM_END - VRAM_BEGIN + 1);
    memset(memory->wram, 0, WRAM_END - WRAM_BEGIN + 1);
    memset(memory->oam, 0, OAM_END - OAM_BEGIN + 1);
    memset(memory->hram, 0, HRAM_END - HRAM_BEGIN + 1);

    init_memory_registers(memory);
}

static void init_memory_registers(Memory* memory) {
    memory->hram[MREG_P1] = 0xcf;
    memory->hram[MREG_SB] = 0x00;
    memory->hram[MREG_SC] = 0x7e;
    memory->hram[MREG_DIV] = 0x18;
    memory->hram[MREG_TIMA] = 0x00;
    memory->hram[MREG_TMA] = 0x00;
    memory->hram[MREG_TAC] = 0xf8;

    memory->hram[MREG_IF] = 0xe1;

    memory->hram[MREG_NR10] = 0x80;
    memory->hram[MREG_NR11] = 0xbf;
    memory->hram[MREG_NR12] = 0xf3;
    memory->hram[MREG_NR13] = 0xff;
    memory->hram[MREG_NR14] = 0xbf;
    memory->hram[MREG_NR21] = 0x3f;
    memory->hram[MREG_NR22] = 0x00;
    memory->hram[MREG_NR23] = 0xff;
    memory->hram[MREG_NR24] = 0xbf;
    memory->hram[MREG_NR30] = 0x7f;
    memory->hram[MREG_NR31] = 0xff;
    memory->hram[MREG_NR32] = 0x9f;
    memory->hram[MREG_NR33] = 0xff;
    memory->hram[MREG_NR34] = 0xbf;
    memory->hram[MREG_NR41] = 0xff;
    memory->hram[MREG_NR42] = 0x00;
    memory->hram[MREG_NR43] = 0x00;
    memory->hram[MREG_NR44] = 0xbf;
    memory->hram[MREG_NR50] = 0x77;
    memory->hram[MREG_NR51] = 0xf3;
    memory->hram[MREG_NR52] = 0xf1;

    memory->hram[MREG_LCDC] = 0x91;
    memory->hram[MREG_STAT] = 0x81;
    memory->hram[MREG_SCY] = 0x00;
    memory->hram[MREG_SCX] = 0x00;
    memory->hram[MREG_LY] = 0x91;
    memory->hram[MREG_LYC] = 0x00;
    memory->hram[MREG_DMA] = 0xff;
    memory->hram[MREG_BGP] = 0xfc;
    memory->hram[MREG_OBP0] = 0x00;
    memory->hram[MREG_OBP1] = 0x00;
    memory->hram[MREG_WY] = 0x00;
    memory->hram[MREG_WX] = 0x00;

    memory->hram[MREG_KEY1] = 0xff;
    memory->hram[MREG_VBK] = 0xff;

    memory->hram[MREG_HDMA1] = 0xff;
    memory->hram[MREG_HDMA2] = 0xff;
    memory->hram[MREG_HDMA3] = 0xff;
    memory->hram[MREG_HDMA4] = 0xff;
    memory->hram[MREG_HDMA5] = 0xff;

    memory->hram[MREG_RP] = 0xff;

    memory->hram[MREG_BCPS] = 0xff;
    memory->hram[MREG_BCPD] = 0xff;
    memory->hram[MREG_OCPS] = 0xff;
    memory->hram[MREG_OCPD] = 0xff;

    memory->hram[MREG_OPRI] = 0x00;
    memory->hram[MREG_SVBK] = 0xff;

    memory->hram[MREG_IE] = 0x00;
}
