#include <stdio.h>
#include "memory.h"

int main(int argc, char const **argv)
{
    mwrite(0x2, 10);

    printf("HELLO WORLD TEST\n");
    return 0;
}
