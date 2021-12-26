/**
 * @file memory.h
 * @author Niklas Seppälä
 * @date 2021-12-21
 * @copyright Copyright (c) 2021
 */


#if !defined(OPCODE_H)
#define OPCODE_H
#include <inttypes.h>

#define OPC_POS 12
#define DEST_REG_POS 9
#define SRC_REG1_POS 6
#define SRC_REG2_POS 0

enum OPCODE 
{
    OP_BR = 0x0,
    OP_ADD,  
    OP_LD,
    OP_ST, 
    OP_JSR,
    OP_AND,
    OP_LDR,
    OP_STR,
    OP_RTI, 
    OP_NOT,
    OP_LDI,
    OP_STI,
    OP_JMP,
    OP_RES,
    OP_LEA,
    OP_TRAP
};

/**
 * @brief 16 bit unsigned integer.
 *    Bit layout:
 *     0000  000  000 0 00000
 *    |___| |__| |__|  |____|
 *    OP    P1   P2    P3
 */
typedef uint16_t instr_t;


/**
 * @brief Executes specified instruction.
 * 
 * @param instruction 16-bit instruction.
 */
void exec_instr(instr_t instruction);


#endif // OPCODE_H
