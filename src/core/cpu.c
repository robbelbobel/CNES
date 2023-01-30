#include "cpu.h"

extern void (*instructions[])(cpu_t*, mmu_t*);

/** FLAG MANAGEMENT **/
void set_flag(cpu_t* cpu, uint8_t flag){
    cpu->p |= flag;
}

void clear_flag(cpu_t* cpu, uint8_t flag){
    cpu->p &= ~flag;
}

cpu_t* create_cpu(){
    // Initialize CPU
    cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
    cpu->cycles = 0;

    return cpu;
}

void step_cpu(cpu_t* cpu, mmu_t* mmu){
    if(--cpu->cycles > 0) return;

    __exec_instr(cpu, mmu);
}

void __exec_instr(cpu_t* cpu, mmu_t* mmu){
    instructions[mmu_read(mmu, cpu->pc)](cpu, mmu);
}