/**
 * @file memory.h
 * @author Niklas Seppälä
 * @brief 
 * @date 2021-12-21
 * @copyright Copyright (c) 2021 MIT
 */


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

/**
 * @brief Reads value from specified memory address.
 * 
 * @param address Operation's target memory address.
 * @return uint16_t Value stored in specified memory address.
 */
uint16_t mread(uint16_t address);

/**
 * @brief Writes specified value to target memory address.
 * 
 * @param address Operation's target memory address.
 * @param val Value to be written in specified memory address.
 */
void mwrite(uint16_t address, uint16_t val);


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
