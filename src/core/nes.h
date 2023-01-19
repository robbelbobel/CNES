#ifndef NES_H
#define NES_H

#include "cpu.h"

typedef struct{
    cpu_t* cpu;
}nes_t;

cpu_t* create_nes();

#endif
