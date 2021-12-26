#include <stdio.h>
#include "memory.h"
#include "opcode.h"
#include <stdio.h>
#include "debug.h"

static void run();

int main(int argc, char const **argv)
{
#ifdef DEBUG
    printf("DEBUG MODE            \033[1;35mactive\033[0m\n");
#ifdef RT_ASSERT
    printf("   * RUNTIME ASSERTS  \033[1;35mactive\033[0m\n");
#endif
    printf("\n");
#endif
    run();
    return 0;
}

static void run()
{
    const enum REGISTER DEST = R_0;
    const enum REGISTER SRC_1 = R_1;
    const enum REGISTER SRC_2 = R_2;

    DEBUG_write_register(__FILE__, __LINE__, SRC_1, 12);
    DEBUG_write_register(__FILE__, __LINE__, SRC_2, 3);
    DEBUG_SECT_END();

    const uint16_t ADD_TEST = DEBUG_build_opc(OP_ADD, DEST, SRC_1, SRC_2);

    exec_instr(ADD_TEST);

    DEBUG_read_register(__FILE__, __LINE__, DEST);
    DEBUG_read_register(__FILE__, __LINE__, SRC_1);
    DEBUG_read_register(__FILE__, __LINE__, SRC_2);
    DEBUG_SECT_END();

}
