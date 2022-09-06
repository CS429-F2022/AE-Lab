#ifndef _ADDS_RI_H_
#define _ADDS_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADDS_RI(instr_t * const);
extern void execute_ADDS_RI(instr_t * const);
#endif