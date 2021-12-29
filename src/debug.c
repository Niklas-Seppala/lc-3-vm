#include <stdarg.h>
#include <time.h>
#include "debug.h"

#define SET_OPC(op) (op << OPC_POS)
#define SET_SRC1_REG(reg) (reg << SRC_REG1_POS)
#define SET_SRC2_REG(reg) (reg << SRC_REG2_POS)
#define SET_DEST_REG(reg) (reg << DEST_REG_POS)

#define TIME_STR_LEN 256
char time_str[TIME_STR_LEN];

char *DEBUG_get_time(char *buffer, size_t n)
{
    time_t timestamp;
    struct tm *details;
    time(&timestamp);
    details = localtime(&timestamp);
    strftime(buffer, 256, "\033[1;33m%d.%m.%Y--%H:%M:%S\033[0m", details);
    return buffer;
}

int DEBUG_comment(const char *comment)
{
    return fprintf(DEBUG_stream(), "\n\033[0;32m// %s\033[0m\n", comment);
}

void DEBUG_instruction(Instruction instr)
{
    const enum OPCODE opc = instr >> OPC_POS;
    char opcode[5];
    opcode_str(opc, opcode, 5);
    printf("%s\n", opcode);
}

void DEBUG_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(DEBUG_stream(), format, args);
    va_end(args);
}

static FILE *stream = NULL;
FILE *DEBUG_stream()
{
    if (!stream)
    {
#ifdef DEBUG_OUTSTREAM
        stream = fopen(DEBUG_OUTSTREAM, "a");
#else
        stream = stdout;
#endif
    }
    return stream;
}

uint16_t DEBUG_build_opc(uint16_t opcode, uint16_t dest_reg,
                         uint16_t src1_reg, uint16_t src2_reg)
{
    return SET_OPC(OPC_ADD) | SET_SRC1_REG(R_1) | SET_SRC2_REG(R_2) | SET_DEST_REG(R_0);
}