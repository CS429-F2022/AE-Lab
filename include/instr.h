/**************************************************************************
 * C S 429 architecture emulator
 * 
 * instr.h - Header file for things related to instructions.
 * 
 * Most of the details will be written in files in the instr/ subdirectory.
 * 
 * Copyright (c) 2022. S. Chatterjee, Si. Nemana. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#ifndef _INSTR_H_
#define _INSTR_H_

#include <stdint.h>
#include <stdbool.h>
#include "reg.h"
#include "mem.h"

#define GETBF(src, frompos, width) safe_GETBF(((int32_t) (src)), (frompos), (width))

/* Used to set condition flags for flag setting instructions
 *
 * N: Negative condition flag
 *      Set to 1 when the result of the instruction is negative
 *      Set to 0 when the result of the instruction is zero or positive
 * Z: Zero condition flag
 *      Set to 1 when the result of the instruction is zero
 *      Set to 0 otherwise
 * C: Carry condition flag
 *      Set to 1 if instruction results in a carry condition, like an unsigned overflow that is the result of an addition
 *      Set to 0 otherwise
 * V: Overflow condition flag
 *      Set to 1 if the instruction results in an overflow condition, like a signed overflow that is the result of an addition
 *      Set to 0 otherwise
 * 
 */

#define PACK_CC(n,z,c,v) (((n)<<3)|((z)<<2)|((c)<<1)|((v)<<0))

//Negative Condition flag
#define GET_NF(cc) (((cc) >> 3)&0x1) 
//Zero Condition flag
#define GET_ZF(cc) (((cc) >> 2)&0x1) 
//Carry Condition flag
#define GET_CF(cc) (((cc) >> 1)&0x1) 
//Overflow Condition flag
#define GET_VF(cc) (((cc) >> 0)&0x1) 

typedef enum opcode {
    OP_NONE,
    // Data transfer
    OP_LDURB,
    OP_LDUR,
    OP_STURB,
    OP_STUR,
    OP_MOVK,
    OP_MOVZ,
    // Computation
    OP_ADD_RI,
    OP_ADDS_RR,
    OP_SUBS_RR,
    OP_MVN,
    OP_ORR_RR,
    OP_EOR_RR,
    OP_ANDS_RR,
    OP_LSL,
    OP_LSR,
    // LSL and LSR are implemented in terms of UBFM
    OP_UBFM, 
    OP_ASR,
    // Control transfer
    OP_B,
    OP_B_COND,
    OP_BL,
    OP_RET,
    // Misc
    OP_NOP,
    OP_HLT,
    OP_ERROR = -1
} opcode_t;

extern opcode_t itable[];

typedef enum cond {
    C_EQ,
    C_NE,
    C_CS,
    C_CC,
    C_MI,
    C_PL,
    C_VS,
    C_VC,
    C_HI,
    C_LS,
    C_GE,
    C_LT,
    C_GT,
    C_LE,
    C_AL,
    C_NV,
    C_ERROR = -1
} cond_t;

typedef enum proc_stage {
    S_FETCH,
    S_DECODE,
    S_EXECUTE,
    S_MEMORY,
    S_WBACK,
    S_UPDATE_PC,
    S_ERROR = -1
} proc_stage_t;

// C1.3.3 p. C1-187
typedef enum addr_mode {
    AM_BASE_ONLY,
    AM_B_PLUS_OFF,
    AM_PRE,
    AM_POST,
    AM_LITERAL,
    AM_ERROR = -1
} addr_mode_t;

typedef struct instr {
// The following fields are relevant to FETCH.
    int32_t     insnbits;   // Bits of instruction.
// The following fields are relevant to DECODE & READ REGISTER FILE.
    opcode_t    op;         // Opcode.
    bool        is_32;      // Flag indicating whether this is the 32-bit version or 64-bit version of the instruction.
    cond_t      cond;       // Branch condition. Relevant only for branch instructions.
    reg_t       *dst;       // Destination register (the one that is written in WB).
    reg_t       *src1;      // Source register 1 (source of first input operand of EX).
    reg_t       *src2;      // Source register 2 (source of second input operand of EX, or source of value for MEM write).
    int64_t     imm;        // Immediate operand (second input operand of EX).
    uint8_t     shift;      // Shift amount, if any.
    uint64_t    next_PC;    // Address of next instruction to be executed. Generally PC+4, but not for B; undefined for RET.
    uint64_t    branch_PC;  // Address of branch target, if any. Undefined for RET.
    // bool        wback;      // Flag relevant for pre- and post-index memory addressing. (NOT NEEDED)
    // bool        postindex;  // Flag relevant for pre- and post-index memory addressing. (NOT NEEDED)
    val_t       opnd1;      // From src1.
    val_t       opnd2;      // From src2 or imm.
// The following fields are relevant to EXECUTE.
    val_t       val_ex;     // Value output of Arithmetic & Logic Unit (ALU).
    val_t       cc;         // Condition code output of ALU.
// The following fields are relevant to ACCESS MEMORY.
    val_t       val_mem;    // Value returned by memory read.
    mrc_t       mrc;        // Return code for memory read/write.
// The following fields are relevant to WRITE BACK REGISTER FILE. (NONE)
// The following fields are relevant to UPDATE PC. (NONE)
} instr_t;

extern unsigned safe_GETBF(int32_t, unsigned, unsigned);
extern void init_itable(void);
extern void fetch_instr(instr_t *const);
extern void decode_instr(instr_t *const);
extern void execute_instr(instr_t *const);
extern void memory_instr(instr_t *const);
extern void wback_instr(instr_t *const);
extern void update_pc_instr(instr_t *const);
extern void show_instr(const instr_t *, const proc_stage_t);
extern void init_itable(void);
#endif