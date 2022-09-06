#ifndef _ORR_RI_H_
#define _ORR_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ORR_RI(instr_t * const);
extern void execute_ORR_RI(instr_t * const);
#endif