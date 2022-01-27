#if !defined(OPC_H)
#define OPC_H
#include <inttypes.h>

enum OPCODE 
{
    OPC_BR = 0x0,
    OPC_ADD,  
    OPC_LD,
    OPC_ST, 
    OPC_JSR,
    OPC_AND,
    OPC_LDR,
    OPC_STR,
    OPC_RTI, 
    OPC_NOT,
    OPC_LDI,
    OPC_STI,
    OPC_JMP,
    OPC_RES,
    OPC_LEA,
    OPC_TRAP
};

enum COND_FLAGS
{
    F_POS  = 0x1,  // Positive flag
    F_ZERO = 0x2,  // Zero flag
    F_NEG  = 0x4   // Negative flag
};

/**
 * @brief 16 bit unsigned integer.
 *    Bit layout:
 *     0000  000  000 0 00000
 *    |___| |__| |__|  |____|
 *    OP    P1   P2    P3
 */
typedef uint16_t Instruction;

/**
 * @brief Executes specified instruction.
 * 
 * @param instr 16-bit instruction.
 */
void exec(Instruction instr);

#endif // OPC_H
