#ifndef _SUB_RI_H_
#define _SUB_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_SUB_RI(instr_t * const);
extern void execute_SUB_RI(instr_t * const);
#endif