#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>

#include "cpu.h"
#include "mmu.h"

void brk(cpu_t* cpu, mmu_t* mmu);
void nop(cpu_t* cpu, mmu_t* mmu);

#endif
