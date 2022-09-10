/**************************************************************************
 * C S 429 architecture emulator
 * 
 * instructions.h - Header file for including instruction-specific details,
 *                  which are in the instr/include sub-directory.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H
#include "LDURB.h"
#include "LDUR.h"
#include "STURB.h"
#include "STUR.h"
#include "MOVK.h"
#include "MOVZ.h"
#include "ADD_RI.h"
#include "ADDS_RR.h"
#include "SUBS_RR.h"
#include "MVN.h"
#include "ORR_RR.h"
#include "EOR_RR.h"
#include "ANDS_RR.h"
#include "LSL.h"
#include "LSR.h"
#include "UBFM.h"
#include "ASR.h"
#include "B.h"
#include "B_COND.h"
#include "BL.h"
#include "RET.h"
#include "NOP.h"
#include "HLT.h"
#include "common_memory.h"
#include "common_writeback.h"
#include "common_update_pc.h"
#endif