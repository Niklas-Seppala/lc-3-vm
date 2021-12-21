/**
 * @file memory.h
 * @author Niklas Seppälä
 * @date 2021-12-21
 * @copyright Copyright (c) 2021
 */



#if !defined(OPCODE_H)
#define OPCODE_H

/**
 * @brief 16 bit unsigned integer.
 *    Bit layout:
 *     0000  000  000 0 00000
 *    |___| |__| |__|  |____|
 *    OP    P1   P2    P3
 */
typedef uint16_t opcode_t;


/**
 * @brief Executes specified instruction.
 * 
 * @param instruction 16-bit instruction.
 */
void exec_instr(uint16_t instruction);


#endif // OPCODE_H
