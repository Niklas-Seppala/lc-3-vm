#include <stdio.h>
#include "memory.h"

int main(int argc, char const **argv)
{
    mread(0x5000);
    printf("HELLO WORLD\n");
    return 0;   
}
