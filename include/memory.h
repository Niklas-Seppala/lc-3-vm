#if !defined(MEMORY_H)
#define MEMORY_H
#include <inttypes.h>

uint16_t mread(uint16_t address);
void mwrite(uint16_t address, uint16_t val);

#endif // MEMORY_H
