#include "opcode.h"
#include <inttypes.h>
#include <stdlib.h>

#define MAX_OP_N 16
// Get the OPCODE from 16-bit instruction (last 4).
#define OPC(instruction) ((instruction) >> 12)

// Function type for operations.
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
static void RES(uint16_t instruction);
static void LEA(uint16_t instruction);
static void TRAP(uint16_t instruction);

// Array of underlying functions for each operation. 
static op_f OPERATIONS[MAX_OP_N] = 
{
    BR,     // 0x0    Conditional branch
    ADD,    // 0x1    Addition
    LD,     // 0x2    Load RPC + offset
    ST,     // 0x3    Store
    JSR,    // 0x4    Jump to subroutine
    AND,    // 0x5    Bitwise AND
    LDR,    // 0x6    Load Base + Offset
    STR,    // 0x7    Store base + offset
    RTI,    // 0x8    Return from interrupt 
    NOT,    // 0x9    Bitwise NOT
    LDI,    // 0xA    Load indirect
    STI,    // 0xB    Store indirect
    JMP,    // 0xC    Jump/Return to subroutine
    RES,    // 0xD   
    LEA,    // 0xE    Load effective address
    TRAP    // 0xF    System trap/call
};

/*****************************************/
/****** Public API Implementations  ******/
/*****************************************/

void exec_instr(uint16_t instruction)
{
    const op_f operation = OPERATIONS[OPC(instruction)];
    operation(instruction);
}
