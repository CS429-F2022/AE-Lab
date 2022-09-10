#include <assert.h>
#include "NOP.h"
#include "machine.h"

extern machine_t guest;

void decode_NOP(instr_t * const insn) {
    assert(insn->insnbits == 0xc503201f);
    return;
}

void execute_NOP(instr_t * const insn) {
    return;
}