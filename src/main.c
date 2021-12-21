#include <stdio.h>
#include "memory.h"
#include "opcode.h"
#include <stdio.h>


int main(int argc, char const **argv)
{
#ifdef DEBUG
    printf("DEBUG MODE            \033[1;35mactive\033[0m\n");
#ifdef RT_ASSERT
    printf("   * RUNTIME ASSERTS  \033[1;35mactive\033[0m\n");
#endif
    printf("\n");
#endif

    mread(0x2);
    printf("HELLO WORLD\n");
    return 0;   
}
