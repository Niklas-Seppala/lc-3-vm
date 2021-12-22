#include "flags.h"
#include "memory.h"

static inline uint16_t negative_16(uint16_t value) { return value >> 15; }
static inline uint16_t positive_16(uint16_t value) { return !(value >> 15); }

/*****************************************/
/****** Public API Implementations  ******/
/*****************************************/

void set_cond_flag(enum REGISTER reg)
{
    const uint16_t value = rread(reg);

    if (value == 0)
        rwrite(R_CND, F_ZERO);

    else if (negative_16(value))
        rwrite(R_CND, F_NEG);

    else
        rwrite(R_CND, F_POS);
}
