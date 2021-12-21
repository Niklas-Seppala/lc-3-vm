#include <inttypes.h>

static uint16_t PC_START = 0x3000;
static uint16_t memory[UINT16_MAX] = {0};

#ifdef DEBUG
#include <assert.h>
#define ILLEGAL_MEMORY_ADDRESS(addr) (addr > PC_START && addr < UINT16_MAX)
#define MEM_RW_ASSERT(addr) assert(ILLEGAL_MEMORY_ADDRESS(addr));
#endif

uint16_t mread(uint16_t address)
{
#ifdef DEBUG
    MEM_RW_ASSERT(address)
#endif

    return memory[address];
}

void mwrite(uint16_t address, uint16_t val)
{
#ifdef DEBUG
    MEM_RW_ASSERT(address)
#endif

    memory[address] = val;
}