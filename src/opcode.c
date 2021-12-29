#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "opcode.h"
#include "memory.h"
#include <string.h>
#include "debug.h"

#define MAX_OP_N 16 // 2^4

#ifdef RT_ASSERT
#include <assert.h>
#define UNDEFINED_OPCODE(opcode) ((opcode >= 0) && (opcode < MAX_OP_N))
#define VALID_OPCODE_ASSERT(opcode) assert(UNDEFINED_OPCODE(opcode))
#endif

#define SIGN_EXTEND_IMM5(instr) (sext_16(mask_immediate(instr), 5))
#define INSTR_VAR_BIT_ACTIVE(instr) ((bool)(instr & 0x20))

/*****************************************/
/******* Private API Declarations ********/
/*****************************************/

/**
 * @brief Sign extend for 16-bit integer. If specified
 *        sign bit is set, left pad the result with ones.
 * 
 * @param value shortened value.
 * @param bit sign bit position.
 * @return uint16_t extended value.
 */
static inline uint16_t sext_16(uint16_t value, const uint16_t sbit);

/**
 * @brief Mask first 5 bits (immediate payload, 5-bit integer)
 *        from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t IMM5 portion of the specified instruction.
 */
static inline uint16_t mask_immediate(Instruction instr);

/**
 * @brief Mask source r1 from instruction. 
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r1.
 */
static inline uint16_t mask_src_r1(Instruction instr);

/**
 * @brief Mask source r2 from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r2.
 */
static inline uint16_t mask_src_r2(Instruction instr);

/**
 * @brief Masks destination register from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t destination register.
 */
static inline uint16_t mask_dest_r(Instruction instr);

// Array of underlying functions for each opcode.
static void (*OP_STORE[MAX_OP_N])(Instruction instr);


/*****************************************/
/****** Public API Implementations  ******/
/*****************************************/

void exec_instr(Instruction instr)
{
    // Opcode from 16-bit instruction (4 msb).
    const uint16_t opcode = instr >> OPC_POS;
#ifdef RT_ASSERT
    VALID_OPCODE_ASSERT(opcode);
#endif
    // Find corresponding op function and exec.
    OP_STORE[opcode](instr);
}


/*****************************************/
/***** Private API Implementations  ******/
/*****************************************/

static inline uint16_t sext_16(uint16_t value, const uint16_t sbit) 
{
    const bool sign_bit = value >> (sbit - 1);
    if (sign_bit) 
        value |= (0xFFFF << sbit);    

    return value;
}

static inline uint16_t mask_immediate(uint16_t instr) 
{ 
    return instr & 0x1F; 
}

static inline uint16_t mask_src_r1(Instruction instr) 
{ 
    return (instr >> SRC_REG1_POS) & 0x7; 
}

static inline uint16_t mask_src_r2(Instruction instr) 
{ 
    return (instr >> SRC_REG2_POS) & 0x7; 
}

static inline uint16_t mask_dest_r(Instruction instr) 
{ 
    return (instr >> DEST_REG_POS) & 0x7; 
}

static void ADD(Instruction instr) 
{
    const uint16_t dest = mask_dest_r(instr);
    const uint16_t param_1 = rread(mask_src_r1(instr));
    uint16_t param_2 = INSTR_VAR_BIT_ACTIVE(instr) 
        ? SIGN_EXTEND_IMM5(instr) 
        : rread(mask_src_r2(instr));

    const uint16_t result = param_1 + param_2;
    rwrite(dest, result);

#ifdef DEBUG
    const int VAR_FLAG = INSTR_VAR_BIT_ACTIVE(instr);
    DEBUG_printf("\n\033[1;35m%s\033[0m    VAR: \033[1;34m%d\033[0m    ", "ADD", VAR_FLAG);
    DEBUG_printf("SRC_1: \033[1;34m0x%X\033[0m   ", param_1);     // SRC_1
    if (VAR_FLAG)
        DEBUG_printf("IMM5: \033[1;34m0x%X\033[0m    ", param_2);  // IMM5
    else
        DEBUG_printf("SRC_2: \033[1;34m0x%X\033[0m    ", param_2); // SRC_2

    DEBUG_printf("\n");
#endif
}


int opcode_str(enum OPCODE opc, char *buffer, int n)
{
    char *str = NULL;
    switch (opc)
    {
    case OPC_BR:   str = "BR  "; break;
    case OPC_ADD:  str = "ADD "; break;
    case OPC_LD:   str = "LD  "; break;
    case OPC_ST:   str = "ST  "; break;
    case OPC_JSR:  str = "JSR "; break;
    case OPC_AND:  str = "AND "; break;
    case OPC_LDR:  str = "LDR "; break;
    case OPC_STR:  str = "STR "; break;
    case OPC_RTI:  str = "RTI "; break;
    case OPC_NOT:  str = "NOT "; break;
    case OPC_LDI:  str = "LDI "; break;
    case OPC_STI:  str = "STI "; break;
    case OPC_JMP:  str = "JMP "; break;
    case OPC_RES:  str = "RES "; break;
    case OPC_LEA:  str = "LEA "; break;
    case OPC_TRAP: str = "TRAP"; break;
    default: return 0;
    }
    strncpy(buffer, str, n);
    return 1;
}

static void AND(Instruction instr) {return;}
static void LD(Instruction instr) {return;}
static void BR(Instruction instr) {return;}
static void ST(Instruction instr) {return;}
static void JSR(Instruction instr) {return;}
static void LDR(Instruction instr) {return;}
static void STR(Instruction instr) {return;}
static void RTI(Instruction instr) {return;}
static void NOT(Instruction instr) {return;}
static void LDI(Instruction instr) {return;}
static void STI(Instruction instr) {return;}
static void JMP(Instruction instr) {return;}
static void RES(Instruction instr) {return;}
static void LEA(Instruction instr) {return;}
static void TRAP(Instruction instr) {return;}

// Array of underlying functions for each opcode.
static void (*OP_STORE[MAX_OP_N])(Instruction instr) = 
{//      bin code | immediate |  description
 //-------------------------------------------------------
    BR,   // 0x0                Conditional branch
    ADD,  // 0x1      Yes       Addition                     
    LD,   // 0x2                Load RPC + offset
    ST,   // 0x3                Store
    JSR,  // 0x4                Jump to subroutine
    AND,  // 0x5      Yes       Bitwise AND
    LDR,  // 0x6                Load Base + Offset
    STR,  // 0x7                Store base + offset
    RTI,  // 0x8                Return from interrupt 
    NOT,  // 0x9                Bitwise NOT
    LDI,  // 0xA                Load indirect
    STI,  // 0xB                Store indirect
    JMP,  // 0xC                Jump
    RES,  // 0xD                RESERVED
    LEA,  // 0xE                Load effective address
    TRAP  // 0xF                System trap/call
};