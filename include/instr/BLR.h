#ifndef _BLR_H_
#define _BLR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BLR(instr_t * const);
extern void execute_BLR(instr_t * const);
#endif