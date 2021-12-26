#include "debug.h"

#define SET_OPC(op) (op << OPC_POS)
#define SET_SRC1_REG(reg) (reg << SRC_REG1_POS)
#define SET_SRC2_REG(reg) (reg << SRC_REG2_POS)
#define SET_DEST_REG(reg) (reg << DEST_REG_POS)

#define DEBUG_LOAD_REG(file, line, reg, value) fprintf(DEBUG_stream(), "%s:%d  LOAD  %s: %*u\n", \
                                           file, line, \
                                           #reg, 8 - (int)((sizeof(#reg)/sizeof(char))), \
                                           value)

#define DEBUG_READ_REG(file, line, reg, value) fprintf(DEBUG_stream(), "%s:%d  READ  %s: %*u\n", \
                                           file, line, \
                                           #reg, 8 - (int)((sizeof(#reg)/sizeof(char))), \
                                           value)

static FILE* debug = NULL;
FILE* DEBUG_stream() 
{
    if (!debug)
    {
#ifdef DEBUG_OUTSTREAM
        debug = fopen(DEBUG_OUTSTREAM);
#else
        debug = stdout;
#endif
    }
    return debug;
}

uint16_t DEBUG_build_opc(uint16_t opcode, uint16_t dest_reg,
                   uint16_t src1_reg, uint16_t src2_reg)
{
    return SET_OPC(OP_ADD) | SET_SRC1_REG(R_1) | SET_SRC2_REG(R_2) | SET_DEST_REG(R_0);
}


uint16_t DEBUG_read_register(char *file, int line, const enum REGISTER reg)
{
    const uint16_t value = rread(reg);
    DEBUG_READ_REG(file, line, reg, value);

    return value;
}

void DEBUG_write_register(char *file, int line, const enum REGISTER reg, uint16_t value)
{
    DEBUG_LOAD_REG(file, line, reg, value);
    rwrite(reg, value);
}
