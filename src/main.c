#include <stdlib.h>
#include "opcodes/opc.h"
#include "memory.h"
#include "trap.h"
#include "io.h"

// Address space OF 0x0 -> 0x3000 is reserved.
static const uint16_t PC_START = 0x3000;

// State of HALT trap.
extern int halt;

static void run_vm(void)
{
    // Initialize program counter.
    rwrite(R_PC, PC_START);
    while (!halt)
    {
        Instruction instr = mread(rread(R_PC));
        incr_rc(1);
        exec(instr);
    }
    clean_io();
}

int main(int argc, char const **argv)
{
    struct args args;
    parse_args(argv, argc, &args);
    printf("%s\n", args.filepath);

    init_io();
    if (!read_img(args.filepath, mem_ptr(NO_OFFSET)))
    {
        printf("Can not open file.\n");
        exit(EXIT_FAILURE);
    }
    run_vm();
    printf("\n");

    return 0;
}