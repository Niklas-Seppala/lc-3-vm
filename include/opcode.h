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

int opcode_str(enum OPCODE opc, char *buffer, int n);


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
void exec_instr(Instruction instr);


#endif // OPCODE_H
