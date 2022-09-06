#ifndef _CBZ_H_
#define _CBZ_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_CBZ(instr_t * const);
extern void execute_CBZ(instr_t * const);
#endif