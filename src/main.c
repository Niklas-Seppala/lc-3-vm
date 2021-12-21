#include <stdio.h>
#include "memory.h"
#include <stdio.h>


int main(int argc, char const **argv)
{
#ifdef RT_ASSERT
    printf("RUNTIME ASSERT active\n");
#endif
#ifdef DEBUG
    printf("DEBUG active\n\n");
#endif

    mread(0x2);
    printf("HELLO WORLD\n");
    return 0;   
}
