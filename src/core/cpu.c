#include "cpu.h"

extern void (*instructions[])(cpu_t*, mmu_t*);

/** FLAG OPERATIONS **/
void set_flag(cpu_t* const cpu, const uint8_t flag, const uint8_t value){
    if(value) cpu->p |= flag;
    else cpu->p &= ~flag;
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
        
        case 0xb1:
            lda_ind_y(cpu, mmu);
            break;

        case 0xb5:
            lda_zpg_x(cpu, mmu);
            break;

        case 0xd8:
            cld(cpu, mmu);
            break;

        case 0xb9:
            lda_abs_y(cpu, mmu);
            break;

        case 0xbd:
            lda_abs_x(cpu, mmu);
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
// ora
void ora_imm(cpu_t* const cpu, mmu_t* const mmu){
    cpu->a |= mmu_read(mmu, cpu->pc + 1);
   
    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 2;
    cpu->pc     += 2;
}

// sei
void sei(cpu_t* const cpu, mmu_t* const mmu){
    set_flag(cpu, FLAG_I, 1);

    cpu->cycles  += 2;
    cpu->pc     += 1;
}

/** LDA **/
// X-Indexed Absolute Addressing
void lda_x_ind(cpu_t* const cpu, mmu_t* const mmu){
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, (((uint16_t) mmu_read(mmu, cpu->x + arg + 1 % 256)) << 8) + mmu_read(mmu, cpu->x + arg % 256));

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 6;
    cpu->pc     += 2;
}

// Zero Page Addressing
void lda_zpg(cpu_t* const cpu, mmu_t* const mmu){
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1); 

    cpu->a = mmu_read(mmu, arg);

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 3;
    cpu->pc     += 2;
}

// Immediate Addressing
void lda_imm(cpu_t* const cpu, mmu_t* const mmu){
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);

    cpu->a = arg;

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 2;
    cpu->pc     += 2;
}

// Absolute Addressing
void lda_abs(cpu_t* const cpu, mmu_t* const mmu){
    const uint16_t arg = (((uint16_t) mmu_read(mmu, cpu->pc + 2)) << 8) + mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, arg);

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 4;
    cpu->pc     += 3;
}

// X-Indexed Absolute Addressing
void lda_abs_x(cpu_t* const cpu, mmu_t* const mmu){
    const uint16_t arg = (((uint16_t) mmu_read(mmu, cpu->pc + 2)) << 8) + mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, arg + cpu->x);

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);
   
    cpu->cycles += (arg & 0xff + cpu->x) > 0xff ? 4 : 3; // Page Boundary Crossing
    cpu->pc     += 3;
}

// Zero Page Indirect Y-Indexed Addressing
void lda_ind_y(cpu_t* const cpu, mmu_t* const mmu){
    printf("Instruction not implemented: LDA IND Y");

    cpu->cycles += 5;
    cpu->pc     += 2;
}

// X-Indexed Zero Page Addressing
void lda_zpg_x(cpu_t* const cpu, mmu_t* const mmu){
    const uint8_t arg = mmu_read(mmu, cpu->pc + 1);
    
    cpu->a = mmu_read(mmu, arg + cpu->x % 256);
    
    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);

    cpu->cycles += 4;
    cpu->pc     += 2;
}

// Y-Indexed Absolute Addressing
void lda_abs_y(cpu_t* const cpu, mmu_t* const mmu){
    const uint16_t arg = ((uint16_t) (mmu_read(mmu, cpu->pc + 2) << 8)) + mmu_read(mmu, cpu->pc + 1);

    cpu->a = mmu_read(mmu, arg + cpu->y);

    set_flag(cpu, FLAG_Z, !cpu->a);
    set_flag(cpu, FLAG_N, cpu->a & MASK_N);
    
    cpu->cycles += (arg & 0xff + cpu->y) > 0xff ? 5 : 4;
    cpu->pc     += 3;
}


// cld
void cld(cpu_t* const cpu, mmu_t* const mmu){
    set_flag(cpu, FLAG_D, 0);

    cpu->cycles  += 2;
    cpu->pc     += 1; 
}

// nop
void nop(cpu_t* const cpu, mmu_t* const mmu){
    cpu->cycles += 2;
    cpu->pc     += 2;
}

