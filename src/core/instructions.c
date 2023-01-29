#include "instructions.h"

void (*instructions[]) = {brk, nop};

void brk(cpu_t* cpu, mmu_t* mmu){

}

void nop(cpu_t* cpu, mmu_t* mmu){

}