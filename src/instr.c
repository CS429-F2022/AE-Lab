/**************************************************************************
 * C S 429 architecture emulator
 * 
 * instr.c - The top-level entry point for instruction processing.
 * 
 * Most of the details will be written in files in the instr/ subdirectory.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "err_handler.h"
#include "instr.h"
#include "machine.h"
#include "instructions.h"

extern machine_t guest;

inline unsigned safe_GETBF(int32_t src, unsigned frompos, unsigned width) {
    return ((((unsigned) src) & (((1 << width) - 1) << frompos)) >> frompos);
}

static inline void init_itable_entry(opcode_t op, unsigned idx) {itable[idx] = op;}

static inline void init_itable_range(opcode_t op, unsigned idx1, unsigned idx2) {
    for (unsigned i = idx1; i <= idx2; i++) itable[i] = op;
}

static inline void init_itable_range_alt(opcode_t op, unsigned idx1, unsigned idx2) {
    for (unsigned i = idx1; i <= idx2; i += 2) itable[i] = op;
}

/*
 * Initialize the itable. Called from interface.c.
 * Do not re-write.
 */

void init_itable(void) {
    for (int i = 0; i < (2<<11); i++) itable[i] = OP_ERROR;
    init_itable_entry(OP_LDURB, 0x1b2U);
    init_itable_entry(OP_LDURH, 0x3b2U);
    init_itable_entry(OP_LDUR, 0x5b2U);
    init_itable_entry(OP_LDUR, 0x7b2U);
    init_itable_entry(OP_STURB, 0x1b0U);
    init_itable_entry(OP_STURH, 0x3b0U);
    init_itable_entry(OP_STUR, 0x5b0U);
    init_itable_entry(OP_STUR, 0x7b0U);
    init_itable_range(OP_MOVK, 0x394U, 0x397U);
    init_itable_range(OP_MOVK, 0x794U, 0x797U);
    init_itable_range(OP_MOVZ, 0x294U, 0x297U);
    init_itable_range(OP_MOVZ, 0x694U, 0x697U);
    init_itable_range(OP_ADD_RI, 0x088U, 0x08bU);
    init_itable_range(OP_ADD_RI, 0x488U, 0x48bU);
    init_itable_range(OP_ADD_RR, 0x058U, 0x05fU);
    init_itable_range(OP_ADD_RR, 0x458U, 0x45fU);
    init_itable_range(OP_ADDS_RI, 0x188U, 0x18bU);
    init_itable_range(OP_ADDS_RI, 0x588U, 0x58bU);
    init_itable_range(OP_ADDS_RR, 0x1a8U, 0x1afU);
    init_itable_range(OP_ADDS_RR, 0x5a8U, 0x5afU);
    init_itable_range(OP_SUB_RI, 0x288U, 0x28bU);
    init_itable_range(OP_SUB_RI, 0x688U, 0x68bU);
    init_itable_range(OP_SUB_RR, 0x258U, 0x25fU);
    init_itable_range(OP_SUB_RR, 0x658U, 0x65fU);
    init_itable_range(OP_SUBS_RI, 0x388U, 0x38bU);
    init_itable_range(OP_SUBS_RI, 0x788U, 0x78bU);
    init_itable_range(OP_SUBS_RR, 0x358U, 0x35fU);
    init_itable_range(OP_SUBS_RR, 0x758U, 0x75fU);
    init_itable_range_alt(OP_MVN, 0x151U, 0x157U);
    init_itable_range_alt(OP_MVN, 0x551U, 0x557U);
    init_itable_range(OP_ORR_RI, 0x190U, 0x193U);
    init_itable_range(OP_ORR_RI, 0x590U, 0x593U);
    init_itable_range_alt(OP_ORR_RR, 0x150U, 0x156U);
    init_itable_range_alt(OP_ORR_RR, 0x550U, 0x556U);
    init_itable_range(OP_EOR_RI, 0x290U, 0x293U);
    init_itable_range(OP_EOR_RI, 0x690U, 0x693U);
    init_itable_range_alt(OP_EOR_RR, 0x250U, 0x256U);
    init_itable_range_alt(OP_EOR_RR, 0x650U, 0x656U);
    init_itable_range(OP_AND_RI, 0x090U, 0x093U);
    init_itable_range(OP_AND_RI, 0x490U, 0x493U);
    init_itable_range_alt(OP_AND_RR, 0x050U, 0x056U);
    init_itable_range_alt(OP_AND_RR, 0x450U, 0x456U);
    init_itable_range(OP_ANDS_RI, 0x390U, 0x393U);
    init_itable_range(OP_ANDS_RI, 0x790U, 0x793U);
    init_itable_range_alt(OP_ANDS_RR, 0x350U, 0x356U);
    init_itable_range_alt(OP_ANDS_RR, 0x750U, 0x756U);
    init_itable_range(OP_UBFM, 0x298U, 0x29bU);
    init_itable_range(OP_UBFM, 0x698U, 0x69bU);
    init_itable_range(OP_ASR, 0x098U, 0x09bU);
    init_itable_range(OP_ASR, 0x498U, 0x49bU);
    init_itable_range(OP_B, 0x0a0U, 0x0abfU);
    init_itable_entry(OP_BR, 0x6b0U);
    init_itable_range(OP_B_COND, 0x2a0U, 0x2a7U);
    init_itable_range(OP_CBNZ, 0x1a8U, 0x1afU);
    init_itable_range(OP_CBNZ, 0x5a8U, 0x5afU);
    init_itable_range(OP_CBZ, 0x1a0U, 0x1a7U);
    init_itable_range(OP_CBZ, 0x5a0U, 0x5a7U);
    init_itable_range(OP_TBNZ, 0x1b8U, 0x1bfU);
    init_itable_range(OP_TBNZ, 0x5b8U, 0x5bfU);
    init_itable_range(OP_TBZ, 0x1b0U, 0x1b7U);
    init_itable_range(OP_TBZ, 0x5b0U, 0x5b7U);
    init_itable_range(OP_BL, 0x4a0U, 0x4bfU);
    init_itable_entry(OP_BLR, 0x6b1U);
    init_itable_entry(OP_RET, 0x6b2U);
    init_itable_entry(OP_NOP, 0x6a8U);
    init_itable_entry(OP_HLT, 0x6a2U);
}

/*
 * Fetch.
 *
 * This is the same for all instructions. Do not re-write.
 */

void fetch_instr(instr_t *const insn) {
    insn->insnbits = mem_read_I(guest.proc->PC.bits->xval);
    return;
}

/*
 * Decode and read operands: top level dispatcher (partially implemented).
 *
 * STUDENT TODO:
 * Finish dispatcher.
 * Finish lower levels in instruction-specific files in the instr/ subdirectory.
 */

void decode_instr(instr_t *const insn) {
    int32_t instr = insn->insnbits;
    unsigned op = GETBF(instr, 21, 11);
    insn->op = itable[op];

    switch(insn->op) {
        case OP_NONE: assert(false); break;
        case OP_LDURB: decode_LDURB(insn); break;
        case OP_LDURH: break;
        case OP_LDUR: break;
        case OP_STURB: decode_STURB(insn); break;
        case OP_STURH: break;
        case OP_STUR: break;
        case OP_MOVK: break;
        case OP_MOVZ: break;
        case OP_ADD_RI: decode_ADD_RI(insn); break;
        case OP_ADD_RR: break;
        case OP_ADDS_RI: break;
        case OP_ADDS_RR: break;
        case OP_SUB_RI: break;
        case OP_SUB_RR: break;
        case OP_SUBS_RI: break;
        case OP_SUBS_RR: break;
        case OP_MVN: break;
        case OP_ORR_RI: break;
        case OP_ORR_RR: break;
        case OP_EOR_RI: break;
        case OP_EOR_RR: break;
        case OP_AND_RI: break;
        case OP_AND_RR: break;
        case OP_ANDS_RI: break;
        case OP_ANDS_RR: break;
        case OP_LSL: break;
        case OP_LSR: break;
        case OP_UBFM: break;
        case OP_ASR: break;
        case OP_B: break;
        case OP_BR: break;
        case OP_B_COND: break;
        case OP_CBNZ: break;
        case OP_CBZ: break;
        case OP_TBNZ: break;
        case OP_TBZ: break;
        case OP_BL: break;
        case OP_BLR: break;
        case OP_RET: break;
        case OP_NOP: decode_NOP(insn); break;
        case OP_HLT: decode_HLT(insn); break;
        case OP_ERROR: assert(false); break;
    }
    return;
}

/*
 * Execute: top level dispatcher (partially implemented).
 *
 * STUDENT TODO:
 * Finish dispatcher.
 * Finish lower levels in instruction-specific files in the instr/ subdirectory.
 */

void execute_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_NONE: assert(false); break;
        case OP_LDURB: execute_LDURB(insn); break;
        case OP_LDURH: break;
        case OP_LDUR: break;
        case OP_STURB: execute_STURB(insn); break;
        case OP_STURH: break;
        case OP_STUR: break;
        case OP_MOVK: break;
        case OP_MOVZ: break;
        case OP_ADD_RI: execute_ADD_RI(insn); break;
        case OP_ADD_RR: break;
        case OP_ADDS_RI: break;
        case OP_ADDS_RR: break;
        case OP_SUB_RI: break;
        case OP_SUB_RR: break;
        case OP_SUBS_RI: break;
        case OP_SUBS_RR: break;
        case OP_MVN: break;
        case OP_ORR_RI: break;
        case OP_ORR_RR: break;
        case OP_EOR_RI: break;
        case OP_EOR_RR: break;
        case OP_AND_RI: break;
        case OP_AND_RR: break;
        case OP_ANDS_RI: break;
        case OP_ANDS_RR: break;
        case OP_LSL: break;
        case OP_LSR: break;
        case OP_UBFM: break;
        case OP_ASR: break;
        case OP_B: break;
        case OP_BR: break;
        case OP_B_COND: break;
        case OP_CBNZ: break;
        case OP_CBZ: break;
        case OP_TBNZ: break;
        case OP_TBZ: break;
        case OP_BL: break;
        case OP_BLR: break;
        case OP_RET: break;
        case OP_NOP: execute_NOP(insn); break;
        case OP_HLT: execute_HLT(insn); break;
        case OP_ERROR: assert(false); break;
    }
    return;
}

/*
 * Access memory: top level dispatcher (partially implemented).
 *
 * STUDENT TODO:
 * Finish dispatcher using lower level routines in the file instr/commmon_memory.c.
 */

void memory_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_NONE: assert(false); break;
        case OP_LDURB: common_memory_load_BW(insn); break;
        case OP_LDURH: break;
        case OP_LDUR: break;
        case OP_STURB: common_memory_store_WB(insn); break;
        case OP_STURH: break;
        case OP_STUR: break;
        case OP_MOVK: break;
        case OP_MOVZ: break;
        case OP_ADD_RI: common_memory_none(insn); break;
        case OP_ADD_RR: break;
        case OP_ADDS_RI: break;
        case OP_ADDS_RR: break;
        case OP_SUB_RI: break;
        case OP_SUB_RR: break;
        case OP_SUBS_RI: break;
        case OP_SUBS_RR: break;
        case OP_MVN: break;
        case OP_ORR_RI: break;
        case OP_ORR_RR: break;
        case OP_EOR_RI: break;
        case OP_EOR_RR: break;
        case OP_AND_RI: break;
        case OP_AND_RR: break;
        case OP_ANDS_RI: break;
        case OP_ANDS_RR: break;
        case OP_LSL: break;
        case OP_LSR: break;
        case OP_UBFM: break;
        case OP_ASR: break;
        case OP_B: break;
        case OP_BR: break;
        case OP_B_COND: break;
        case OP_CBNZ: break;
        case OP_CBZ: break;
        case OP_TBNZ: break;
        case OP_TBZ: break;
        case OP_BL: break;
        case OP_BLR: break;
        case OP_RET: break;
        case OP_NOP: common_memory_none(insn); break;
        case OP_HLT: common_memory_none(insn); break;
        case OP_ERROR: assert(false); break;
    }
    return;
}

/*
 * Write back to register file: top level dispatcher (partially implemented).
 *
 * STUDENT TODO:
 * Finish dispatcher using lower level routines in the file instr/common_writeback.c.
 */

void wback_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_NONE: assert(false); break;
        case OP_LDURB: common_writeback_mem_W(insn); break;
        case OP_LDURH: case OP_LDUR: 
            break;
        case OP_STURB: case OP_STURH: case OP_STUR: common_writeback_none(insn); break;
        case OP_MOVK: case OP_MOVZ: 
            break;
        case OP_ADD_RI: case OP_ADD_RR: case OP_ADDS_RI: case OP_ADDS_RR: 
        case OP_SUB_RI: case OP_SUB_RR: case OP_SUBS_RI: case OP_SUBS_RR: 
        case OP_MVN: 
        case OP_ORR_RI: case OP_ORR_RR: case OP_EOR_RI: case OP_EOR_RR: 
        case OP_AND_RI: case OP_AND_RR: 
        case OP_ANDS_RI: case OP_ANDS_RR: 
        case OP_LSL: case OP_LSR: case OP_UBFM: case OP_ASR: 
            common_writeback_alu_X(insn); break;
        case OP_B: break;
        case OP_BR: break;
        case OP_B_COND: break;
        case OP_CBNZ: break;
        case OP_CBZ: break;
        case OP_TBNZ: break;
        case OP_TBZ: break;
        case OP_BL: break;
        case OP_BLR: break;
        case OP_RET: break;
        case OP_NOP: common_writeback_none(insn); break;
        case OP_HLT: common_writeback_none(insn); break;
        case OP_ERROR: assert(false); break;
    }
    return;
}

/*
 * Update PC: top level dispatcher (partially implemented).
 *
 * STUDENT TODO:
 * Finish dispatcher using lower level routines in the file instr/common_update_pc.c.
 */

void update_pc_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_NONE: 
            assert(false); break;
        case OP_LDURB: case OP_LDURH: case OP_LDUR: 
        case OP_STURB: case OP_STURH: case OP_STUR: 
        case OP_MOVK: case OP_MOVZ: 
        case OP_ADD_RI: case OP_ADD_RR: case OP_ADDS_RI: case OP_ADDS_RR: 
        case OP_SUB_RI: case OP_SUB_RR: case OP_SUBS_RI: case OP_SUBS_RR: 
        case OP_MVN: 
        case OP_ORR_RI: case OP_ORR_RR: case OP_EOR_RI: case OP_EOR_RR: 
        case OP_AND_RI: case OP_AND_RR: 
        case OP_ANDS_RI: case OP_ANDS_RR: 
        case OP_LSL: case OP_LSR: case OP_UBFM: case OP_ASR: 
            update_pc_next(insn); break;
        case OP_B: 
            break;
        case OP_BR: 
            break;
        case OP_B_COND: 
            break;
        case OP_CBNZ: 
            break;
        case OP_CBZ: 
            break;
        case OP_TBNZ: 
            break;
        case OP_TBZ: 
            break;
        case OP_BL: 
            break;
        case OP_BLR: 
            break;
        case OP_RET: 
            break;
        case OP_NOP: update_pc_next(insn); break;
        case OP_HLT: update_pc_halt(insn); break;
        case OP_ERROR: assert(false); break;
    }
    return;
}

#ifdef DEBUG
static char *opcode_names[] = {
    "ERR ", 
    "LDURB ",
    "LDURH ",
    "LDUR ",
    "STURB ",
    "STURH ",
    "STUR ",
    "MOVK ",
    "MOVZ ",
    "ADD ",
    "ADD ",
    "ADDS ",
    "ADDS ",
    "SUB ",
    "SUB ",
    "SUBS ",
    "SUBS ",
    "MVN ",
    "ORR ",
    "ORR ",
    "EOR ",
    "EOR ",
    "AND ",
    "AND ",
    "ANDS ",
    "ANDS ",
    "LSL ",
    "LSR ",
    "ASR ",
    "B ",
    "BR ",
    "B.cond ",
    "CBNZ ",
    "CBZ ",
    "TBNZ ",
    "TBZ ",
    "BL ",
    "BLR ",
    "RET ",
    "NOP ",
    "HLT ",
};

static char *cond_names[] = {
    "EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", 
    "HI", "LS", "GE", "LT", "GT", "LE", "AL", "NV"
};
#endif

/*
 * A debugging aid to print out the fields of an instruction.
 * 
 * Only S_FETCH and S_DECODE stages are fully implemented.
 * The remaining stages are an optional STUDENT TODO.
 * The DEBUG flag will be turned off during auto-grading.
 */

void show_instr(const instr_t * insn, const proc_stage_t stage) {
#ifdef DEBUG
    switch (stage) {
        case S_FETCH:
            printf("F:[%08lX  %08X]\n", guest.proc->PC.bits->xval, insn->insnbits);
            break;
        case S_DECODE:
            printf(" D:\t\t\t[%s\t%s\t%s\t%s\t%s\t%016lX\t%d\t%c\t%c]\n", 
                opcode_names[insn->op], 
                insn->cond ? cond_names[insn->cond] : "--",
                insn->dst ? insn->dst->name : "---",
                insn->src1 ? insn->src1->name : "---",
                insn->src2 ? insn->src2->name : "---",
                insn->imm, 
                insn->shift,
                insn->wback ? 'Y' : 'N',
                insn->postindex ? 'Y' : 'N');
            break;

        case S_EXECUTE: 
            printf("  X:\n");
            break;
        case S_MEMORY: 
            printf("   M:\n");
            break;
        case S_WBACK: 
            printf("    W:\n");
            break;
        case S_UPDATE_PC: 
            printf("     U:\n");
            break;
        default: assert(false); break;
    }
#endif
    return;
}