#include <stdio.h>

#include "core/nes.h"

int main(){
    /** INITIALIZATION **/
    nes_t* nes = create_nes();

    free(nes);

    return 0;
}