# Definitions

CC = gcc
CC_FLAGS = -Wall -ggdb -DDEBUG -Iinclude -Iinclude/instr 
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
LD = gcc
LIBS = -ldl
MD = gccmakedep

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: tidy depend ae clean

ae: 
	(cd src && make $@)
	${CC} ${CC_FLAGS} -I instr -o $@ `/bin/ls src/*.o src/instr/*.o`

depend:
	(cd src && make $@)

clean:
	(cd src && make $@)
	${RM} *.o *.so *.bak

tidy:
	${RM} ae

count:
	wc -l src/*.c src/instr/*.c | tail -n 1
	wc -l include/*.h include/instr/*.h | tail -n 1

# DO NOT DELETE