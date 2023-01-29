#ifndef CPU_H
#define CPU_H

#include "stdlib.h"
#include "stdint.h"

typedef struct{
    // Registers
    uint8_t A;      // Accumulator
    uint8_t X, Y;   // Indexes
    uint16_t PC;    // Program Counter
    uint8_t S;      // Stack Pointer
    uint8_t P;      // Status Register

    // Additional
    uint8_t cycles;
}cpu_t;

cpu_t* create_cpu();
void cpu_step();

#endif