#ifndef _ANDS_RI_H_
#define _ANDS_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ANDS_RI(instr_t * const);
extern void execute_ANDS_RI(instr_t * const);
#endif