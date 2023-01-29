#include "nes.h"

nes_t* create_nes(){
    // Allocate NES
    nes_t* nes = (nes_t*) malloc(sizeof(nes_t));

    // Attach Components
    nes->cpu = create_cpu();
    nes->mmu = create_mmu();

    return nes;
}