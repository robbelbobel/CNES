#ifndef CPU_H
#define CPU_H

#include "stdlib.h"
#include "stdint.h"

#include "mmu.h"

#include "stdio.h"

#define FLAG_C 0b00000001
#define FLAG_Z 0b00000010
#define FLAG_I 0b00000100
#define FLAG_D 0b00001000
#define FLAG_V 0b01000000
#define FLAG_N 0b10000000

typedef struct{
    // Registers
    uint8_t a;      // Accumulator
    uint8_t x, y;   // Indexes
    uint16_t pc;    // Program Counter
    uint8_t s;      // Stack Pointer
    uint8_t p;      // Status Register

    // Additional
    uint8_t cycles;
}cpu_t;


cpu_t* create_cpu();

void set_flag(cpu_t* cpu, uint8_t flag);
void clear_flag(cpu_t* cpu, uint8_t flag);

void step_cpu(cpu_t* cpu, mmu_t* mmu);
void __exec_instr(cpu_t* cpu, mmu_t* mmu);

#endif