#ifndef _TBNZ_H_
#define _TBNZ_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_TBNZ(instr_t * const);
extern void execute_TBNZ(instr_t * const);
#endif