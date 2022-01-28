#if !defined(MEMORY_H)
#define MEMORY_H
#include <inttypes.h>

/**
 * @brief LC-3 Registers. Last value is used as the
 *        register count.
 * 
 */
enum REGISTER  
{
    R_0 = 0,
    R_1,
    R_2,
    R_3,
    R_4,
    R_5,
    R_6,
    R_7,
    R_PC,  // Program counter.
    R_CND, // Dedicaded conditional register.
    R_SIZE // Total count of registers (10).
};

enum MEMMAP {
  MR_KBSR = 0xFE00, // keyboard status
  MR_KBDR = 0xFE02  // keyboard data
};

/**
 * @brief Reads value from specified memory address.
 * 
 * @param address Operation's target memory address.
 * @return uint16_t Value stored in specified memory address.
 */
uint16_t mread(uint16_t address);

#define NO_OFFSET 0

/**
 * @brief Get pointer to memory + offset.
 * 
 * @param offset Offset to address 0x0.
 * @return uint16_t* Memory pointer.
 */
uint16_t *mem_ptr(uint16_t offset);

/**
 * @brief Writes specified value to target memory address.
 * 
 * @param address Operation's target memory address.
 * @param val Value to be written in specified memory address.
 */
void mem_write(uint16_t address, uint16_t val);

/**
 * @brief Increments program counter by specified offset.
 * 
 * @param offset program counter offset.
 */
void incr_rc(uint16_t offset);

/**
 * @brief Reads value from specified register.
 * 
 * @param reg Operation's target register.
 * @return uint16_t Value stored in specified register.
 */
uint16_t rread(enum REGISTER reg);

/**
 * @brief Writes specified value to target register.
 * 
 * @param reg Operation's target register.
 * @param val Value to be written in specified register.
 */
void rwrite(enum REGISTER reg, uint16_t val);


#endif // MEMORY_H
