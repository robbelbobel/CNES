#include <stdio.h>

#include "core/instructions.h"

extern void (*instructions[1])(nes_t* nes);

int main(){
    /** INITIALIZATION **/
    nes_t* nes = create_nes();

    instructions[0](nes);

    return 0;
}