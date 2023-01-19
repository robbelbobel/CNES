#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>

typedef struct{
    // Registers
    uint8_t A;      // Accumulator
    uint8_t X, Y;   // Indexes
    uint16_t PC;    // Program Counter
    uint8_t S;      // Stack Pointer
    uint8_t P;      // Status Register
}cpu_t;

#endif