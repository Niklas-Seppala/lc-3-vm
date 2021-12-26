#if !defined(DEBUG_H)
#define DEBUG_H
#include <inttypes.h>
#include "memory.h"
#include "opcode.h"
#include <stdio.h>

#define DEBUG_SECT_END() fprintf(DEBUG_stream(), "\n")

/**
 * @brief Get the debug stream. Defaults to stdout.
 * 
 * @return FILE* Debug stream.
 */
FILE* DEBUG_stream();

/**
 * @brief Builds mock opcode from specified parameters.
 * 
 * @param opcode Opcode (ADD, LD, JMP etc..)
 * @param dest_reg Operation destination register.
 * @param src1_reg Operation param1 register.
 * @param src2_reg Operation param2 register.
 * @return uint16_t Complete opcode.
 */
uint16_t DEBUG_build_opc(uint16_t opcode, uint16_t dest_reg,
                   uint16_t src1_reg, uint16_t src2_reg);

/**
 * @brief 
 * 
 * @param file 
 * @param line 
 * @param reg 
 * @return uint16_t 
 */
uint16_t DEBUG_read_register(char *file, int line, const enum REGISTER reg);

/**
 * @brief 
 * 
 * @param file 
 * @param line 
 * @param reg 
 * @return uint16_t 
 */
void DEBUG_write_register(char *file, int line, const enum REGISTER reg, uint16_t value);

#endif // DEBUG_H
