#include <stdio.h>
#include "trap.h"
#include "memory.h"

int halt = 0;

static inline void t_getc(void)
{
    rwrite(R_0, getc(stdin));
}

static inline void t_outc(void)
{
    fputc((char)rread(R_0), stdout);
}

static inline void t_puts(void)
{
    uint16_t *str = mem_ptr(rread(R_0));
    if (!*str) return;
    while (*str)
        fputc((char)*str++, stdout);
    fflush(stdout);
    
}

static inline void t_in(void)
{
    const char c = fgetc(stdin);
    rwrite(R_0, c);
    fputc(c, stdout);
}

static inline void t_halt(void)
{
    halt = 1;
}

static inline void t_in_u16(void)
{
    printf("> ");
    uint16_t val;
    fscanf(stdin, "%hu", &val);
    rwrite(R_0, val);
}

static inline void t_out_u16(void)
{
    fprintf(stdout, "%hu\n", rread(R_0));
}

static inline void t_putsp(void) 
{
    uint16_t* wc = mem_ptr(rread(R_0));
    while (*wc)
    {
        char char1 = (*wc) & 0xFF;
        putc(char1, stdout);
        char char2 = (*wc) >> 8;
        if (char2) putc(char2, stdout);
        ++wc;
    }
    fflush(stdout);
}

static void (*TRAP_STORE[8])(void) =
{
    t_getc, t_outc,
    t_puts, t_putsp,
    t_in, t_halt,
    t_in_u16, t_out_u16
};

void exec_trap(uint16_t trapvect)
{
    TRAP_STORE[trapvect - TRAP_OFFSET]();
}
