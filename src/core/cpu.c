#include "cpu.h"

cpu_t* create_cpu(){
    // Initialize CPU
    cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
    cpu->cycles = 0;

    return cpu;
}