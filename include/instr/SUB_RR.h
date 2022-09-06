#ifndef _SUB_RR_H_
#define _SUB_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_SUB_RR(instr_t * const);
extern void execute_SUB_RR(instr_t * const);
#endif