# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -UDEBUG -I../../include  -I../../include/instr
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

SRCS := \
ADD_RI.c ADD_RR.c ADDS_RI.c ADDS_RR.c AND_RI.c AND_RR.c ANDS_RI.c ANDS_RR.c ASR.c \
B.c B_COND.c BL.c BLR.c BR.c \
CBNZ.c CBZ.c \
EOR_RI.c EOR_RR.c \
HLT.c \
LDURB.c LDUR.c LDURH.c LSL.c LSR.c \
MOVK.c MOVZ.c MVN.c \
NOP.c \
ORR_RI.c ORR_RR.c \
RET.c \
STURB.c STUR.c STURH.c SUB_RI.c SUB_RR.c SUBS_RI.c SUBS_RR.c \
TBNZ.c TBZ.c \
UBFM.c \
common_memory.c common_writeback.c common_update_pc.c
# SRCS := $(HDRS:%.h=%.c)
OBJS := $(SRCS:%.c=%.o)

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: depend ae clean

ae: ${OBJS}

depend:
	${MD} -- ${CC_OPTIONS} ${CC_FLAGS} -- ${SRCS}

clean:
	${RM} *.o *.so *.bak

# DO NOT DELETE
ADD_RI.o: ADD_RI.c \
 ../../include/instr/ADD_RI.h \
 ../../include/instr/../instr.h \
 ../../include/instr/../reg.h ../../include/instr/../mem.h \
 ../../include/machine.h ../../include/proc.h ../../include/reg.h \
 ../../include/mem.h

ADD_RR.o: ADD_RR.c ADDS_RI.c ADDS_RR.c AND_RI.c AND_RR.c ANDS_RI.c ANDS_RR.c ASR.c B.c B_COND.c BL.c BLR.c BR.c CBNZ.c CBZ.c EOR_RI.c EOR_RR.c HLT.c LDURB.c LDUR.c LDURH.c LSL.c LSR.c MOVK.c MOVZ.c MVN.c NOP.c ORR_RI.c ORR_RR.c RET.c STURB.c STUR.c STURH.c SUB_RI.c SUB_RR.c SUBS_RI.c SUBS_RR.c TBNZ.c TBZ.c UBFM.c common_memory.c \
 ../../include/err_handler.h \
 ../../include/instr.h ../../include/reg.h ../../include/mem.h \
 ../../include/machine.h ../../include/proc.h
common_writeback.o: common_writeback.c \
 ../../include/err_handler.h \
 ../../include/instr.h ../../include/reg.h ../../include/mem.h \
 ../../include/machine.h ../../include/proc.h
common_update_pc.o: common_update_pc.c \
 ../../include/machine.h \
 ../../include/proc.h \
 ../../include/reg.h \
 ../../include/mem.h ../../include/instr.h 
