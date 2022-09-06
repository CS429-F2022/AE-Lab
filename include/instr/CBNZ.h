#ifndef _CBNZ_H_
#define _CBNZ_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_CBNZ(instr_t * const);
extern void execute_CBNZ(instr_t * const);
#endif