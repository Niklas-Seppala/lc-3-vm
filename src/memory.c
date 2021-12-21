#include <inttypes.h>
#include "memory.h"

static uint16_t PC_START = 0x3000;         // Addresses < 0x3000 reserved for later use.
static uint16_t memory[UINT16_MAX] = {0};  // Program Memory. 
static uint16_t registers[R_SIZE] = {0};   // Program Register.

/*****************************************/
/***** Runtime R/W safety assertions *****/
/*****************************************/
#ifdef RT_ASSERT
#include <assert.h>
#define ILLEGAL_MEMORY_ACCESS(addr) (addr > PC_START && addr < UINT16_MAX)
#define ILLEGAL_REGISTER_ACCESS(reg) (reg >= R_0 && reg < R_SIZE)

#define MEMORY_RW_ASSERT(addr) assert(ILLEGAL_MEMORY_ACCESS(addr))
#define REGISTER_RW_ASSERT(reg) assert(ILLEGAL_REGISTER_ACCESS(reg))
#endif


/*****************************************/
/************* Public API  ***************/
/*****************************************/

uint16_t rread(enum REGISTER reg)
{
#ifdef RT_ASSERT
    REGISTER_RW_ASSERT(reg);
#endif
    return registers[reg];
}

void rwrite(enum REGISTER reg, uint16_t val)
{
#ifdef RT_ASSERT
    REGISTER_RW_ASSERT(reg);
#endif
    registers[reg] = val;
}

uint16_t mread(uint16_t address)
{
#ifdef RT_ASSERT
    MEMORY_RW_ASSERT(address);
#endif

    return memory[address];
}

void mwrite(uint16_t address, uint16_t val)
{
#ifdef RT_ASSERT
    MEMORY_RW_ASSERT(address);
#endif

    memory[address] = val;
}