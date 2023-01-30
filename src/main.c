#include <stdio.h>

#include "core/nes.h"

int main(){
    /** INITIALIZATION **/
    nes_t* nes = create_nes();

    while(1) step_nes(nes);

    return 0;
}