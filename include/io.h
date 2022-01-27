#if !defined(IO_H)
#define IO_H

#include <inttypes.h>
#include <stdio.h>
#include "opcodes/opc.h"

#define RST  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

struct args
{
    const char *filepath;
};

#define CLEAR() printf("\033[H\033[J")
#define GOTO_XY(x,y) printf("\033[%d;%dH", (y), (x))

void init_io(void);
void clean_io(void);

int read_img(const char *path, uint16_t *memory);
void parse_args(const char **argv, const int argc, struct args *args);
#endif // IO_H
