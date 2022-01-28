#if !defined(IO_H)
#define IO_H

#include <stdio.h>
#include "opcodes/opc.h"

// #define CLEAR() printf("\033[H\033[J")
// #define GOTO_XY(x,y) printf("\033[%d;%dH", (y), (x))

struct args
{
    const char *filepath;
};

void init_io(void);
void clean_io(void);

int read_img(const char *path, uint16_t *memory);
void parse_args(const char **argv, const int argc, struct args *args);

#endif // IO_H
