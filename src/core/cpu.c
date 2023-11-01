#include "cpu.h"

extern void (*instructions[])(cpu_t*, mmu_t*);

/** FLAG OPERATIONS **/
void set_flag(cpu_t* const cpu, const uint8_t flag){
    cpu->p |= flag;
}

void clear_flag(cpu_t* const cpu, const uint8_t flag){
    cpu->p &= ~flag;
}

/** CPU FUNCTIONS **/
cpu_t* create_cpu(){
    // Initialize CPU
    cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
    cpu->cycles = 0;

    return cpu;
}

void step_cpu(cpu_t* const cpu, mmu_t* const mmu){
    if(--cpu->cycles > 0) return;

    __exec_instr(cpu, mmu);
}

void __exec_instr(cpu_t* const cpu, mmu_t* const mmu){
    switch(mmu_read(mmu, cpu -> pc)){
        case 0x78:
            sei(cpu, mmu);
            break;
        
        case 0xa1:
            lda_x_ind(cpu, mmu);
            break;

        case 0xa5:
            lda_zpg(cpu, mmu);
            break;
           
        case 0xa9:
            lda_imm(cpu, mmu);
            break;

        case 0xad:
            lda_abs(cpu, mmu);
            break;

        case 0xd8:
            cld(cpu, mmu);
            break;

        case 0xea:
            nop(cpu, mmu);
            break; 

        default:
            // Invalid Instruction
            cpu->pc += 1;
            break;
    }
}

/** INSTRUCTIONS **/
// ORA
void ora_imm(cpu_t* const cpu, mmu_t* const mmu){
    cpu->a |= mmu_read(mmu, cpu->pc + 1);
    
    if(cpu->a) clear_flag(cpu, FLAG_Z);
    else set_flag(cpu, FLAG_Z);

    if(cpu->a & 0x80) set_flag(cpu, FLAG_N);
    else clear_flag(cpu, FLAG_N);

    cpu->cycles += 2;
    cpu->pc     += 2;
}

// SEI
void sei(cpu_t* const cpu, mmu_t* const mmu){
    set_flag(cpu, FLAG_I);

    cpu->cycles  += 2;
    cpu->pc     += 1;
}

// LDA
void lda_x_ind(cpu_t* const cpu, mmu_t* const mmu){
    // X-Indexed Absolute Addressing
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, (((uint16_t) mmu_read(mmu, cpu->x + arg + 1 % 0xff)) << 8) + mmu_read(mmu, cpu->x + arg % 0xff));

    if(cpu->a)          clear_flag(cpu, FLAG_Z);
    if(cpu->a & MASK_N) set_flag(cpu, FLAG_N);

    cpu->cycles  += 6;
    cpu->pc     += 2;
}

void lda_zpg(cpu_t* const cpu, mmu_t* const mmu){
    // Zero Page Addressing
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1); 

    cpu->a = mmu_read(mmu, arg);

    if(cpu->a)          clear_flag(cpu, FLAG_Z);
    if(cpu->a & MASK_N) set_flag(cpu, FLAG_N);

    cpu->cycles  += 3;
    cpu->pc     += 2;
}

void lda_imm(cpu_t* const cpu, mmu_t* const mmu){
    // Immediate Addressing
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);

    cpu->a = arg;

    if(cpu->a)          clear_flag(cpu, FLAG_Z);
    if(cpu->a & MASK_N) set_flag(cpu, FLAG_N);

    cpu->cycles  += 2;
    cpu->pc     += 2;
}

void lda_abs(cpu_t* const cpu, mmu_t* const mmu){
    // Absolute Addressing
    const uint16_t arg = (((uint16_t) mmu_read(mmu, cpu->pc + 2)) << 8) + mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, arg);

    if(cpu->a)          clear_flag(cpu, FLAG_Z);
    if(cpu->a & MASK_N) set_flag(cpu, FLAG_N);

    cpu->cycles  += 4;
    cpu->pc     += 3;
}

void lda_ind_y(cpu_t* const cpu, mmu_t* const mmu){
    // Zero Page Indirect Y-Indexed Addressing
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);
}

void lda_abs_x(cpu_t* const cpu, mmu_t* const mmu){
    const uint16_t arg = (((uint16_t) mmu_read(mmu, cpu->pc + 2)) << 8) + mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, arg + cpu->x);

    if(cpu->a)          clear_flag(cpu, FLAG_Z);
    if(cpu->a & MASK_N) set_flag(cpu, FLAG_N);
    
    cpu->cycles  += (arg + cpu->x) > 0xff ? 4 : 3; // Page Boundary Crossing
    cpu->pc     += 3;
}


// CLD
void cld(cpu_t* const cpu, mmu_t* const mmu){
    clear_flag(cpu, FLAG_D);

    cpu->cycles  += 2;
    cpu->pc     += 1; 
}

// NOP
void nop(cpu_t* const cpu, mmu_t* const mmu){
    cpu->cycles += 2;
    cpu->pc     += 2;
}

