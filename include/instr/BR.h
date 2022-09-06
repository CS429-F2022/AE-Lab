#ifndef _BR_H_
#define _BR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BR(instr_t * const);
extern void execute_BR(instr_t * const);
#endif