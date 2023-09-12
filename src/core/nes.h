#ifndef NES_H
#define NES_H

#include "cpu.h"
#include "mmu.h"

typedef struct{
    cpu_t* cpu;
    mmu_t* mmu;
}nes_t;

nes_t* create_nes();

void step_nes(nes_t* const nes);

#endif
