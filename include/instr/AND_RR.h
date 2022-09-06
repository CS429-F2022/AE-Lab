#ifndef _AND_RR_H_
#define _AND_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_AND_RR(instr_t * const);
extern void execute_AND_RR(instr_t * const);
#endif