#if !defined(TRAP_H)
#define TRAP_H
#include <stdio.h>
#include <inttypes.h>


#define TRAP_OFFSET 0x20

/**
 * @brief Executes trap routine.
 * 
 * @param trapvect Trap.
 */
void exec_trap(uint16_t trapvect);


// bool is_running();

#endif // TRAP_H
