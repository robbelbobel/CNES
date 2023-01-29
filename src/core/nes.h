#ifndef NES_H
#define NES_H

#include "cpu.h"
#include "mmu.h"
#include "instructions.h"

typedef struct{
    cpu_t* cpu;
    mmu_t* mmu;
}nes_t;

nes_t* create_nes();

#endif
