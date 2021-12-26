#include "memory.h"

uint8_t* access_memory(Memory memory, uint8_t* address) {
    if (ptr_in(address, VRAM_BEGIN, VRAM_END)) {
        return &(memory.vram[ptr_offset(address, VRAM_BEGIN)]);
    } else if (ptr_in(address, WRAM_BEGIN, WRAM_END)) {
        return &(memory.wram[ptr_offset(address, WRAM_BEGIN)]);
    } else if (ptr_in(address, OAM_BEGIN, OAM_END)) {
        return &(memory.oam[ptr_offset(address, OAM_BEGIN)]);
    } else if (ptr_in(address, HRAM_BEGIN, HRAM_END)) {
        return &(memory.hram[ptr_offset(address, HRAM_BEGIN)]);
    } else {
        fprintf(stderr, "Memory access violation: (%p)\n", (void*) address);
        return NULL;
    }
}
