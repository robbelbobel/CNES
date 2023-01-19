#include "nes.h"

cpu_t* create_nes(){
    // Create Components
    cpu_t* cpu = malloc(sizeof(cpu_t));
    nes_t* nes = malloc(sizeof(nes_t));
    
    // Link Components
    nes->cpu = cpu;

    return cpu;
}