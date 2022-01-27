#include "opcodes/opc.h"
#include "opcodes/utils.h"
#include "memory.h"
#include "trap.h"

#define MAX_OP_N 16

static void set_flags(enum REGISTER reg)
{
    const uint16_t value = reg_read(reg);

    if (value == 0)
        reg_write(R_CND, F_ZERO);

    else if (negative_16(value)) {
        reg_write(R_CND, F_NEG);
    }

    else
        reg_write(R_CND, F_POS);
}

/*****************************************/
/******** OPCODE IMPLEMENTATIONS  ********/
/*****************************************/

static void (*OP_STORE[MAX_OP_N])(Instruction instr);

static void ADD(Instruction instr) 
{
    const bool VAR = var_set(instr, 5);
    uint16_t dest = mask_dest_r(instr);
    uint16_t param_1 = reg_read(mask_src_r1(instr));
    uint16_t param_2 = VAR 
        ? SIGN_EXTEND_IMM5(instr) 
        : reg_read(mask_src_r2(instr));

    uint16_t result = param_1 + param_2;
    reg_write(dest, result);
    set_flags(dest);
}

static void AND(Instruction instr)
{
    const bool VAR = var_set(instr, 5);

    uint16_t dest = mask_dest_r(instr);
    uint16_t param_1 = reg_read(mask_src_r1(instr));
    uint16_t param_2 = VAR 
        ? SIGN_EXTEND_IMM5(instr) 
        : reg_read(mask_src_r2(instr));
    uint16_t result = param_1 & param_2;
    reg_write(dest, result);
    set_flags(dest);
}

static void LD(Instruction instr)
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t PC = reg_read(R_PC);
    uint16_t offset = SIGN_EXTEND_OFF9(instr);
    uint16_t mem_value = mem_read(PC + offset);
    reg_write(dest, mem_value);
    set_flags(dest);
}

static void LDI(Instruction instr)
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t pc_offset = SIGN_EXTEND_OFF9(instr);
    uint16_t mem_value = mem_read(mem_read(reg_read(R_PC) + pc_offset));
    reg_write(dest, mem_value);
    set_flags(dest);
}

static void LDR(Instruction instr) 
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t src_1 = mask_src_r1(instr);
    uint16_t offset = SIGN_EXTEND_OFF6(instr);
    uint16_t val = reg_read(src_1) + offset;
    reg_write(dest, mem_read(val));
    set_flags(dest);
}

static void LEA(Instruction instr) 
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t offset = SIGN_EXTEND_OFF9(instr);
    uint16_t value = reg_read(R_PC) + offset;
    reg_write(dest, value);
    set_flags(dest);
}

static void BR(Instruction instr) 
{
    if (reg_read(R_CND) & mask_conds(instr))
    {
        uint16_t offset = SIGN_EXTEND_OFF9(instr);
        reg_write(R_PC, reg_read(R_PC) + offset);
    }
}

static void ST(Instruction instr) 
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t offset = SIGN_EXTEND_OFF9(instr);
    mem_write(reg_read(R_PC) + offset, reg_read(dest));
}

static void JSR(Instruction instr) 
{
    reg_write(R_7, reg_read(R_PC));

    if (var_set(instr, 11))
    {
        uint16_t long_offset = SIGN_EXTEND_OFF11(instr);
        reg_write(R_PC, reg_read(R_PC) + long_offset);
    }
    else
    {
        uint16_t baser = reg_read(mask_src_r1(instr));
        reg_write(R_PC, baser);
    }
}

static void STR(Instruction instr)
{
    uint16_t value = reg_read(mask_dest_r(instr));
    uint16_t offset = SIGN_EXTEND_OFF6(instr);
    uint16_t baser = reg_read(mask_src_r1(instr));

    mem_write(baser + offset, value);
}

static void NOT(Instruction instr)
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t param_1 = reg_read(mask_src_r1(instr));
    reg_write(dest, ~param_1);
    set_flags(dest);
}

static void STI(Instruction instr)
{
    uint16_t dest = mask_dest_r(instr);
    uint16_t offset = SIGN_EXTEND_OFF9(instr);
    mem_write(mem_read(reg_read(R_PC) + offset), reg_read(dest));
}

static void JMP(Instruction instr)
{
    uint16_t baser = mask_src_r1(instr);
    reg_write(R_PC, reg_read(baser));
}

static void TRAP(Instruction instr) 
{
    uint16_t trapvec = mask_trapvect(instr);
    exec_trap(trapvec);
}

// RESERVED / UNIMPLEMENTED
static void RTI(Instruction instr) {return;}
static void RES(Instruction instr) {return;}

// Array of underlying functions for each opcode.
static void (*OP_STORE[MAX_OP_N])(Instruction instr) = 
{//       code   |  var  |  cond  | description
 //-------------------------------------------------------
    BR,   // 0x0                    Conditional branch
    ADD,  // 0x1    Yes     Yes     Addition                     
    LD,   // 0x2            Yes     Load RPC + offset
    ST,   // 0x3                    Store
    JSR,  // 0x4    Yes             Jump to subroutine
    AND,  // 0x5    Yes     Yes     Bitwise AND
    LDR,  // 0x6            Yes     Load Base + Offset
    STR,  // 0x7                    Store base + offset
    RTI,  // 0x8                    Return from interrupt (not implemented)
    NOT,  // 0x9            Yes     Bitwise NOT
    LDI,  // 0xA            Yes     Load indirect
    STI,  // 0xB                    Store indirect
    JMP,  // 0xC                    Jump
    RES,  // 0xD                    RESERVED
    LEA,  // 0xE            Yes     Load effective address
    TRAP  // 0xF                    System trap/call
};

#ifdef RT_ASSERT
#include <assert.h>
#define UNDEFINED_OPCODE(opcode) ((opcode >= 0) && (opcode < MAX_OP_N))
#define VALID_OPCODE_ASSERT(opcode) assert(UNDEFINED_OPCODE(opcode))
#endif

void exec_instr(Instruction instr)
{
    // Opcode from 16-bit instruction (4 msb).
    const uint16_t opcode = instr >> OPC_POS;
#ifdef RT_ASSERT
    VALID_OPCODE_ASSERT(opcode);
#endif
    static char OPC_BUFFER[5];
    opcode_str(opcode, OPC_BUFFER, 5); 
    // printf("OP: %s\n", OPC_BUFFER);
    // Find corresponding op function and exec.
    OP_STORE[opcode](instr);

}