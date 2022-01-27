#if !defined(OPCODE_UTILS_H)
#define OPCODE_UTILS_H
#include "opcodes/utils.h"
#include "opcodes/opc.h"
#include <stdbool.h>

#define OPC_POS 12
#define DEST_REG_POS 9
#define CONDS_POS 9
#define SRC1_POS 6
#define SRC2_POS 0

/**
 * @brief Check if value is negative.
 * 
 * @param value unsigned 16-bit integer
 */
bool negative_16(uint16_t value);

/**
 * @brief Check if value is positive.
 * 
 * @param value unsigned 16-bit integer
 */
bool positive_16(uint16_t value);

/**
 * @brief Sign extend for 16-bit integer. If specified
 *        sign bit is set, left pad the result with ones.
 * 
 * @param value shortened value.
 * @param bit sign bit position.
 * @return uint16_t extended value.
 */
uint16_t sext_16(uint16_t value, const uint16_t sbit);

/**
 * @brief 
 * 
 * @param instr 
 * @return uint16_t 
 */
uint16_t mask_trapvect(Instruction instr);

/**
 * @brief Mask first 5 bits (immediate payload, 5-bit integer)
 *        from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t IMM5 portion of the specified instruction.
 */
uint16_t mask_immediate(Instruction instr);

/**
 * @brief Mask first 9 offset bits from instruction.
 * 
 * @param instr 16-bit instruction.
 * @return uint16_t 9-bit OFFSET9 portion of the specified instruction.
 */
uint16_t mask_offs9(Instruction instr);

/**
 * @brief 
 * 
 * @param instr 
 * @return uint16_t 
 */
uint16_t mask_offs6(Instruction instr);

/**
 * @brief 
 * 
 * @param instr 
 * @return uint16_t 
 */
uint16_t mask_conds(Instruction instr);

/**
 * @brief 
 * 
 * @param instr 
 * @return uint16_t 
 */
uint16_t mask_offs11(Instruction instr);

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

bool var_set(Instruction instr, int n);

int opcode_str(enum OPCODE opc, char *buffer, int n);

#define SIGN_EXTEND_IMM5(instr) (sext_16(mask_immediate(instr), 5))
#define SIGN_EXTEND_OFF9(instr) (sext_16(mask_offs9(instr), 9))
#define SIGN_EXTEND_OFF6(instr) (sext_16(mask_offs6(instr), 6))
#define SIGN_EXTEND_OFF11(instr) (sext_16(mask_offs11(instr), 11))

#endif // OPCODE_UTILS_H
