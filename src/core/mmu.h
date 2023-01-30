#ifndef MMU_H
#define MMU_H

#define MMU_INTERNAL_RAM_SZ     0x0800
#define MMU_RAM_MIRRORS_SZ      3 * MMU_INTERNAL_RAM_SZ
#define MMU_PPU_REGISTERS_SZ    0x0008
#define MMU_PPU_MIRRORS_SZ      0x1ff8
#define MMU_IO_REGISTERS_SZ     0x0018
#define MMU_TEST_SZ             0x0008
#define MMU_CARTRIDGE_SZ        0xBFE0

#include "stdlib.h"
#include "stdint.h"

typedef struct{
    uint8_t internal_ram[MMU_INTERNAL_RAM_SZ];
    uint8_t cartridge[MMU_CARTRIDGE_SZ];
}mmu_t;


mmu_t* create_mmu();

void mmu_write(mmu_t* mmu, uint16_t address, uint8_t value);
uint8_t mmu_read(mmu_t* mmu, uint16_t address);

#endif