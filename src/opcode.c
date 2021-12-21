#include "opcode.h"
#include <inttypes.h>
#include <stdlib.h>

#define MAX_OP_N 16
#define OPC(instruction) ((instruction) >> 12)

typedef void (*op_f)(uint16_t instruction);

// TODO: Implement operations later.
static void ADD(uint16_t instruction);
static void AND(uint16_t instruction);
static void LD(uint16_t instruction);
static void BR(uint16_t instruction);
static void ST(uint16_t instruction);
static void JSR(uint16_t instruction);
static void LDR(uint16_t instruction);
static void STR(uint16_t instruction);
static void RTI(uint16_t instruction);
static void NOT(uint16_t instruction);
static void LDI(uint16_t instruction);
static void STI(uint16_t instruction);
static void JMP(uint16_t instruction);
static void LEA(uint16_t instruction);
static void TRAP(uint16_t instruction);

static op_f OPERATIONS[MAX_OP_N] = 
{
    BR, ADD, LD,
    ST, JSR, AND,
    LDR, STR, RTI,
    NOT, LDI, STI,
    JMP, NULL, LEA,
    TRAP
};

void exec_instr(uint16_t instruction)
{
    const op_f operation = OPERATIONS[OPC(instruction)];
    operation(instruction);
}
