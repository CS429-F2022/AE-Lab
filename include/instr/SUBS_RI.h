#ifndef _SUBS_RI_H_
#define _SUBS_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_SUBS_RI(instr_t * const);
extern void execute_SUBS_RI(instr_t * const);
#endif