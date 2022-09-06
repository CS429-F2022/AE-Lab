#ifndef _TBZ_H_
#define _TBZ_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_TBZ(instr_t * const);
extern void execute_TBZ(instr_t * const);
#endif