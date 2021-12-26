/**
 * @file flags.h
 * @author Niklas Seppälä
 * @date 2021-12-21
 * @copyright Copyright (c) 2021
 */


#if !defined(FLAGS_H)
#define FLAGS_H
#include "memory.h"

/**
 * @brief Conditional flags:
 *           Positive,
 *           Negative,
 *           Zero
 */
enum COND_FLAGS
{
    F_POS = 1 << 0,  // Positive flag
    F_ZERO = 1 << 1, // Zero flag
    F_NEG = 1 << 2   // Negative flag
};

/**
 * @brief Sets condition flag based on underlying
 *        value of specified register.
 * 
 * @param reg operation result register.
 */
void set_cond_flag(enum REGISTER reg);

#endif // FLAGS_H
