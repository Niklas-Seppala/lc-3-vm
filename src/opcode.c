#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "opcode.h"
#include "memory.h"

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
static inline uint16_t mask_immediate(uint16_t instr);

/**
 * @brief Mask source r1 from instruction. 
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r1.
 */
static inline uint16_t mask_src_r1(uint16_t instr);

/**
 * @brief Mask source r2 from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r2.
 */
static inline uint16_t mask_src_r2(uint16_t instr);

/**
 * @brief Masks destination register from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t destination register.
 */
static inline uint16_t mask_dest_r(uint16_t instr);

// Array of underlying functions for each opcode.
static void (*OP_STORE[MAX_OP_N])(uint16_t instruction);


/*****************************************/
/****** Public API Implementations  ******/
/*****************************************/

void exec_instr(uint16_t instr)
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

static inline uint16_t mask_src_r1(uint16_t instr) 
{ 
    return (instr >> SRC_REG1_POS) & 0x7; 
}

static inline uint16_t mask_src_r2(uint16_t instr) 
{ 
    return (instr >> SRC_REG2_POS) & 0x7; 
}

static inline uint16_t mask_dest_r(uint16_t instr) 
{ 
    return (instr >> DEST_REG_POS) & 0x7; 
}

static void ADD(uint16_t instr) 
{
    const uint16_t dest = mask_dest_r(instr);
    const uint16_t param_1 = rread(mask_src_r1(instr));
    uint16_t param_2 = INSTR_VAR_BIT_ACTIVE(instr) 
        ? SIGN_EXTEND_IMM5(instr) 
        : rread(mask_src_r2(instr));

    const uint16_t result = param_1 + param_2;
    rwrite(dest, result);
}

static void AND(uint16_t instruction) {return;}
static void LD(uint16_t instruction) {return;}
static void BR(uint16_t instruction) {return;}
static void ST(uint16_t instruction) {return;}
static void JSR(uint16_t instruction) {return;}
static void LDR(uint16_t instruction) {return;}
static void STR(uint16_t instruction) {return;}
static void RTI(uint16_t instruction) {return;}
static void NOT(uint16_t instruction) {return;}
static void LDI(uint16_t instruction) {return;}
static void STI(uint16_t instruction) {return;}
static void JMP(uint16_t instruction) {return;}
static void RES(uint16_t instruction) {return;}
static void LEA(uint16_t instruction) {return;}
static void TRAP(uint16_t instruction) {return;}

// Array of underlying functions for each opcode.
static void (*OP_STORE[MAX_OP_N])(uint16_t instruction) = 
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