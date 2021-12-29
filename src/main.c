#include <stdio.h>
#include "memory.h"
#include "opcode.h"
#include <stdio.h>
#include "debug.h"
#include <time.h>

static void run();

int main(int argc, char const **argv)
{
#ifdef DEBUG
    char buffer[256];
    DEBUG_get_time(buffer, 256);
    DEBUG_printf("%s\n", buffer);
    
    DEBUG_printf("DEBUG MODE                  \033[1;32mactive\033[0m\n");
    // printf("Current local time and date: %s\n", asctime(timeinfo));
    // DEBUG_printf("");
#ifdef RT_ASSERT
    DEBUG_printf("   * RUNTIME MEMORY SAFETY  \033[1;32mactive\033[0m\n");
#endif
#endif
    run();
    DEBUG_printf("\n");
    return 0;
}

static void run()
{
    const enum REGISTER DEST = R_0;
    const enum REGISTER SRC_1 = R_1;
    const enum REGISTER SRC_2 = R_2;

    DEBUG_comment("PRE ADD");
    DEBUG_WRITE_REG(__FILE__, __LINE__, SRC_1, 12);
    DEBUG_WRITE_REG(__FILE__, __LINE__, SRC_2, 3);

    const Instruction ADD = DEBUG_build_opc(OPC_ADD, DEST, SRC_1, SRC_2);
    exec_instr(ADD);

    DEBUG_comment("AFTER ADD");
    DEBUG_READ_REG(__FILE__, __LINE__, SRC_1);
    DEBUG_READ_REG(__FILE__, __LINE__, SRC_2);
    DEBUG_READ_REG(__FILE__, __LINE__, DEST);
}
