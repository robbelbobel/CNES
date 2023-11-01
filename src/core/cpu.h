#ifndef CPU_H
#define CPU_H

#include "stdlib.h" #include "stdint.h"

#include "mmu.h"

#include "stdio.h"

#define MASK_N 0b10000000

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

// Flag Operations
void set_flag(cpu_t* const cpu, const uint8_t flag);
void clear_flag(cpu_t* const cpu, const uint8_t flag);

// CPU Functions
cpu_t* create_cpu();

void step_cpu(cpu_t* const cpu, mmu_t* const mmu);
void __exec_instr(cpu_t* const cpu, mmu_t* const mmu);

/** INSTRUCTIONS **/
// ora
void ora_imm(cpu_t* const cpu, mmu_t* const mmu);
// sei
void sei(cpu_t* const cpu, mmu_t* const mmu);
// LDA
void lda_x_ind(cpu_t* const cpu, mmu_t* const mmu);
void lda_zpg(cpu_t* const cpu, mmu_t* const mmu);
void lda_imm(cpu_t* const cpu, mmu_t* const mmu);
void lda_abs(cpu_t* const cpu, mmu_t* const mmu);

void lda_ind_y(cpu_t* const cpu, mmu_t* const mmu);
void lda_zpg_x(cpu_t* const cpu, mmu_t* const mmu);
void lda_abs_y(cpu_t* const cpu, mmu_t* const mmu);
void lda_abs_x(cpu_t* const cpu, mmu_t* const mmu);

// cld
void cld(cpu_t* const cpu, mmu_t* const mmu);
// nop
void nop(cpu_t* const cpu, mmu_t* const mmu);

#endif
