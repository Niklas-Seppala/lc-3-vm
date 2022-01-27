#include "trap.h"
#include "memory.h"
#include "stdbool.h"
#include <stdlib.h>

static bool RUNNING = true;

static inline void t_getc(void)
{
    reg_write(R_0, getc(stdin));
}

static inline void t_outc(void)
{
    fputc((char)reg_read(R_0), stdout);
}

static inline void t_puts(void)
{
    uint16_t *str = mem_ptr(reg_read(R_0));
    if (!*str) return;
    while (*str)
        fputc((char)*str++, stdout);
    fflush(stdout);
    
}

static inline void t_in(void)
{
    const char c = fgetc(stdin);
    reg_write(R_0, c);
    fputc(c, stdout);
}

static inline void t_halt(void)
{
    RUNNING = false;
}

static inline void t_in_u16(void)
{
    printf("> ");
    uint16_t val;
    fscanf(stdin, "%hu", &val);
    reg_write(R_0, val);
}

static inline void t_out_u16(void)
{
    fprintf(stdout, "%hu\n", reg_read(R_0));
}

static void (*TRAP_STORE[8])(void) =
{
    t_getc, t_outc,
    t_puts, NULL,
    t_in, t_halt,
    t_in_u16, t_out_u16
};

void exec_trap(uint16_t trapvect)
{
    TRAP_STORE[trapvect - TRAP_OFFSET]();
}

bool is_running(void) 
{
    return RUNNING; 
}