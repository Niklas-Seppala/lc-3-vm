#if !defined(DEBUG_H)
#define DEBUG_H
#include <inttypes.h>
#include <stdio.h>
#include "memory.h"
#include "opcode.h"

// These weird macros are for debugging io.
// #define DEBUG_COMMENT(label) fprintf(DEBUG_stream(), "\n\033[0;32m// %s\033[0m\n", label)
#define DEBUG_WRITE_REG(file, line, reg, value) {fprintf(DEBUG_stream(), "%s:%d  \033[0;35mWRITE\033[0m  %-5s:  \033[1;34m0x%X\033[0m\n", \
                                           file, line, \
                                           #reg, value); \
                                           rwrite(reg, value);}

#define DEBUG_READ_REG(file, line, reg) {fprintf(DEBUG_stream(), "%s:%d  \033[0;36mREAD\033[0m   %-5s:  \033[1;34m0x%X\033[0m\n", \
                                           file, line, \
                                           #reg, rread(reg)); }

/**
 * @brief Get the debug stream. Defaults to stdout.
 * 
 * @return FILE* Debug stream.
 */
FILE* DEBUG_stream();


void DEBUG_instruction(Instruction instr);

int DEBUG_comment(const char *comment);

char* DEBUG_get_time(char *buffer, size_t n);

void DEBUG_printf(const char *format, ...);

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


#endif // DEBUG_H
