#include <stdio.h>
#include "memory.h"
#include "opcode.h"
#include <stdio.h>


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
    const uint16_t instruction = (0 | OP_ADD) ;
    exec_instr(instruction);
}
