#if !defined(OPCODE_UTILS_H)
#define OPCODE_UTILS_H

#include "opcodes/utils.h"
#include "opcodes/opc.h"

/**
 * @brief Check if value is negative.
 * 
 * @param value unsigned 16-bit integer
 */
int negative_16(uint16_t value);

/**
 * @brief Check if value is positive.
 * 
 * @param value unsigned 16-bit integer
 */
int positive_16(uint16_t value);

/**
 * @brief Sign extend for 16-bit integer. If specified
 *        sign bit is set, left pad the result with ones.
 * 
 * @param value shortened value.
 * @param bit sign bit position.
 * @return uint16_t extended value.
 */
uint16_t sext(uint16_t value, const uint16_t sbit);

/**
 * @brief Mask first 8 bits (trap).
 * 
 * @param instr 16 bit instruction
 * @return uint16_t trap op
 */
uint16_t mask_trapvect(Instruction instr);

/**
 * @brief Mask opcode from specified instruction.
 *        Casted OPCODE to enum.
 * 
 * @param instr 16 bit instruction.
 * @return enum OPCODE 4 bit instr
 */
enum OPCODE mask_opcode(Instruction instr);

/**
 * @brief Mask first 5 bits (immediate payload, 5-bit integer)
 *        from instruction.
 * 
 * @param instr 16 bit instruction.
 * @return uint16_t IMM5 portion of the specified instruction.
 */
uint16_t mask_immediate(Instruction instr);

/**
 * @brief Mask first 9 offset bits from instruction.
 * 
 * @param instr 16 bit instruction.
 * @return uint16_t 9 bit OFFSET9 portion of instruction.
 */
uint16_t mask_offs9(Instruction instr);

/**
 * @brief Mask first 6 bits from instruction.
 * 
 * @param instr 16 bit instruction.
 * @return uint16_t 6 bit OFFSET6 portion of instruction.
 */
uint16_t mask_offs6(Instruction instr);

/**
 * @brief Mask first 11 bits from instruction.
 * 
 * @param instr 16 bit instruction.
 * @return uint16_t 11 bit OFFSET11 portion of instruction.
 */
uint16_t mask_offs11(Instruction instr);

/**
 * @brief Mask conditional bits from instruction.
 * 
 * @param instr 16 bit instruction.
 * @return uint16_t conditional bits.
 */
uint16_t mask_conds(Instruction instr);

/**
 * @brief Mask source r1 from instruction. 
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r1.
 */
uint16_t mask_src_r1(Instruction instr);

/**
 * @brief Mask source r2 from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t source r2.
 */
uint16_t mask_src_r2(Instruction instr);

/**
 * @brief Masks destination register from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t destination register.
 */
uint16_t mask_dest_r(Instruction instr);

/**
 * @brief Check if the specified instruction has active
 *        var bit.
 * 
 * @param instr 16 bit instruction.
 * @param n var bit location.
 */
int var_set(Instruction instr, int n);

#define SIGN_EXTEND_IMM5(instr)  (sext(mask_immediate(instr), 5))
#define SIGN_EXTEND_OFF9(instr)  (sext(mask_offs9(instr), 9))
#define SIGN_EXTEND_OFF6(instr)  (sext(mask_offs6(instr), 6))
#define SIGN_EXTEND_OFF11(instr) (sext(mask_offs11(instr), 11))

#endif // OPCODE_UTILS_H
