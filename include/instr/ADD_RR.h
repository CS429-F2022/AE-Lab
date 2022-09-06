#ifndef _ADD_RR_H_
#define _ADD_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADD_RR(instr_t * const);
extern void execute_ADD_RR(instr_t * const);
#endif