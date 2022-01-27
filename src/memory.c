#include <inttypes.h>
#include "memory.h"
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static uint16_t PC_START = 0x3000;        // Addresses < 0x3000 reserved for later use.
static uint16_t memory[UINT16_MAX] = {0}; // Program Memory.
static uint16_t registers[R_SIZE] = {0};  // Program Register.

/*****************************************/
/***** Runtime R/W safety assertions *****/
/*****************************************/
#ifdef RT_ASSERT
#include <assert.h>
#include <stdio.h>

#define ILLEGAL_MEMORY_ACCESS 0
#define ILLEGAL_REG_ACCESS 0

static void mem_rw_assert(uint16_t addr)
{
    int valid = (addr >= PC_START && addr < UINT16_MAX);
    if (!valid)
    {
        fprintf(stderr, "invalid memory address: 0x%x\n", addr);
        assert(ILLEGAL_MEMORY_ACCESS);
    }
}

static void reg_rw_assert(uint16_t reg)
{
    int valid = (reg >= R_0 && reg < R_SIZE);
    if (!valid)
    {
        fprintf(stderr, "invalid register: 0x%x\n", reg);
        assert(ILLEGAL_REG_ACCESS);
    }
}
#endif

/*****************************************/
/****** Public API Implementations  ******/
/*****************************************/

uint16_t rread(enum REGISTER reg)
{
#ifdef RT_ASSERT
    reg_rw_assert(reg);
#endif
    return registers[reg];
}

void rwrite(enum REGISTER reg, uint16_t val)
{
#ifdef RT_ASSERT
    reg_rw_assert(reg);
#endif
    registers[reg] = val;
}

inline void incr_rc(uint16_t offset)
{
    rwrite(R_PC, rread(R_PC) + offset);
}

static uint16_t check_key()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

#include <stdio.h>
uint16_t mread(uint16_t address)
{
#ifdef RT_ASSERT
    mem_rw_assert(address);
#endif

    if (address == MR_KBSR)
    {
        if (check_key())
        {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        }
        else
        {
            memory[MR_KBSR] = 0;
        }
    }
    return memory[address];
}

void mem_write(uint16_t address, uint16_t val)
{
#ifdef RT_ASSERT
    mem_rw_assert(address);
#endif

    memory[address] = val;
}

uint16_t *mem_ptr(uint16_t offset)
{
    return (memory + offset);
}