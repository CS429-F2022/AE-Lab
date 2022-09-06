#ifndef _AND_RI_H_
#define _AND_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_AND_RI(instr_t * const);
extern void execute_AND_RI(instr_t * const);
#endif