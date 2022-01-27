#include "opcodes/utils.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

inline bool negative_16(uint16_t value)
{ 
    return value >> 15;
}

inline bool positive_16(uint16_t value)
{ 
    return !(value >> 15); 
}

inline uint16_t sext_16(uint16_t value, const uint16_t sbit)
{
    const bool sign_bit = value >> (sbit - 1);
    if (sign_bit & 1) {
        value |= (0xFFFF << sbit);
    }

    return value;
}

inline uint16_t mask_trapvect(Instruction instr)
{
    return instr & 0xFF;
}

inline uint16_t mask_immediate(uint16_t instr)
{
    return instr & 0x1F;
}

inline uint16_t mask_offs9(Instruction instr)
{
    return instr & 0x1FF;
}

inline uint16_t mask_offs6(Instruction instr)
{
    return instr & 0x3F;
}

inline uint16_t mask_offs11(Instruction instr)
{
    return instr & 0x7FF;
}

inline uint16_t mask_conds(Instruction instr)
{
    return (instr >> CONDS_POS) & 0x7;
}

inline uint16_t mask_src_r1(Instruction instr)
{
    return (instr >> SRC1_POS) & 0x7;
}

inline uint16_t mask_src_r2(Instruction instr)
{
    return (instr >> SRC2_POS) & 0x7;
}

inline uint16_t mask_dest_r(Instruction instr)
{
    return (instr >> DEST_REG_POS) & 0x7;
}

inline bool var_set(Instruction instr, int n)
{
    return (instr >> n) & 1;
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
    default:
        return 0;
    }
    strncpy(buffer, str, n);
    return 1;
}
