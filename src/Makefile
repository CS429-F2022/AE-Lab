# STUDENTS: DO NOT MODIFY.
#
# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -DDEBUG -I../include -I../include/instr
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

SRCS := \
archsim.c \
elf_loader.c err_handler.c \
handle_args.c \
instr.c interface.c \
machine.c mem.c \
proc.c ptable.c \
reg.c
OBJS := $(SRCS:%.c=%.o)

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: depend ae clean

ae: ${OBJS}
	(cd instr && make $@)

depend:
	(cd instr && make $@)
	${MD} -- ${CC_OPTIONS} ${CC_FLAGS} -- ${SRCS}

clean:
	(cd instr && make $@)
	${RM} *.o *.so *.bak

# DO NOT DELETE
archsim.o: archsim.c ../include/archsim.h \
 ../include/ansicolors.h ../include/err_handler.h ../include/machine.h \
 ../include/proc.h ../include/reg.h ../include/mem.h ../include/instr.h \
 ../include/elf_loader.h
elf_loader.o: elf_loader.c \
 ../include/err_handler.h \
 ../include/mem.h
err_handler.o: err_handler.c \
 ../include/archsim.h \
 ../include/ansicolors.h ../include/err_handler.h ../include/machine.h \
 ../include/proc.h ../include/reg.h ../include/mem.h ../include/instr.h \
 ../include/elf_loader.h ../include/ansicolors.h
handle_args.o: handle_args.c \
 ../include/archsim.h \
 ../include/ansicolors.h ../include/err_handler.h ../include/machine.h \
 ../include/proc.h ../include/reg.h ../include/mem.h ../include/instr.h \
 ../include/elf_loader.h
instr.o: instr.c \
 ../include/err_handler.h \
 ../include/instr.h ../include/reg.h ../include/mem.h \
 ../include/machine.h ../include/proc.h ../include/instructions.h \
 ../include/instr/ADD_RI.h ../include/instr/../instr.h \
 ../include/instr/common_memory.h ../include/instr/common_writeback.h \
 ../include/instr/common_update_pc.h
interface.o: interface.c ../include/archsim.h \
 ../include/ansicolors.h ../include/err_handler.h ../include/machine.h \
 ../include/proc.h ../include/reg.h ../include/mem.h ../include/instr.h \
 ../include/elf_loader.h ../include/ansicolors.h
machine.o: machine.c \
 ../include/machine.h ../include/proc.h \
 ../include/reg.h \
 ../include/mem.h
mem.o: mem.c \
 ../include/err_handler.h ../include/mem.h ../include/ptable.h \
 ../include/machine.h ../include/proc.h ../include/reg.h ../include/mem.h
proc.o: proc.c ../include/archsim.h \
 ../include/ansicolors.h ../include/err_handler.h ../include/machine.h \
 ../include/proc.h ../include/reg.h ../include/mem.h ../include/instr.h \
 ../include/elf_loader.h
ptable.o: ptable.c \
 ../include/ptable.h \
 reg.c \
 ../include/reg.h 
