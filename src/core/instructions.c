#include "instructions.h"

/** INSTRUCTIONS **/
void (*instructions[])(cpu_t*, mmu_t*) = {brk, nop};

// BRK
void brk(cpu_t* cpu, mmu_t* mmu){

}

// ORA
void ora_imm(cpu_t* cpu, mmu_t* mmu){
    cpu->a |= mmu_read(mmu, cpu->pc + 1);
    
    if(cpu->a) clear_flag(cpu, FLAG_Z);
    else set_flag(cpu, FLAG_Z);

    if(cpu->a & 0x80) set_flag(cpu, FLAG_N);
    else clear_flag(cpu, FLAG_N);

    cpu->cycles += 2;
    cpu->pc += 2;
}

// ASL
void asl(cpu_t* cpu, mmu_t* mmu){

}

// PHP
void php(cpu_t* cpu, mmu_t* mmu){

}

// BPL
void bpl(cpu_t* cpu, mmu_t* mmu){
    
}

// CLC
void clc(cpu_t* cpu, mmu_t* mmu){
    
}

// JSR
void jsr(cpu_t* cpu, mmu_t* mmu){

}

// AND
void and(cpu_t* cpu, mmu_t* mmu){

}

// BIT
void bit(cpu_t* cpu, mmu_t* mmu){
    
}

// ROL
void rol(cpu_t* cpu, mmu_t* mmu){
    
}

// PLP
void plp(cpu_t* cpu, mmu_t* mmu){
    
}

// BMI
void bmi(cpu_t* cpu, mmu_t* mmu){
    
}

// SEC
void sec(cpu_t* cpu, mmu_t* mmu){

}

// RTI
void rti(cpu_t* cpu, mmu_t* mmu){

}

// EOR
void eor(cpu_t* cpu, mmu_t* mmu){

}

// LSR
void lsr(cpu_t* cpu, mmu_t* mmu){

}

// JMP
void jmp(cpu_t* cpu, mmu_t* mmu){

}

// NOP
void nop(cpu_t* cpu, mmu_t* mmu){

}