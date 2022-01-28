#include "opcodes/utils.h"

#define OPC_POS 12
#define DEST_REG_POS 9
#define CONDS_POS 9
#define SRC1_POS 6
#define SRC2_POS 0

inline int negative_16(uint16_t value)
{ 
    return value >> 15;
}

inline int positive_16(uint16_t value)
{ 
    return !(value >> 15); 
}

inline uint16_t sext(uint16_t value, const uint16_t sbit)
{
    int sign_bit = value >> (sbit - 1);
    if (sign_bit & 1) {
        value |= (0xFFFF << sbit);
    }

    return value;
}


inline enum OPCODE mask_opcode(Instruction instr)
{
    return (instr >> OPC_POS);
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

inline int var_set(Instruction instr, int n)
{
    return (instr >> n) & 1;
}
