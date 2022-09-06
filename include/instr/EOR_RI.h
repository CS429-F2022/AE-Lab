#ifndef _EOR_RI_H_
#define _EOR_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_EOR_RI(instr_t * const);
extern void execute_EOR_RI(instr_t * const);
#endif