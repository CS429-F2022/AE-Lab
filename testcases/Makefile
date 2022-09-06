GCC = aarch64-linux-gnu-gcc
OPTFLAG = -O3

OBJDUMP = aarch64-linux-gnu-objdump
OD = od
RM = /bin/rm -f
CHMOD = chmod go+rx

TESTCASES = \
gcd \
hello helloint \
qsort \
test_switch \
vecsum

%.o: %.c
	${GCC} ${OPTFLAG} -c $<

all:
	docker build -t arm .
	docker run -v `pwd`:/work -t arm

binaries: gcd hello helloint qsort test_switch vecsum 

gcd: Makefile gcd.c
	@echo "+-----+"
	@echo "| gcd |"
	@echo "+-----+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

hello: Makefile hello.c
	@echo "+-------+"
	@echo "| hello |"
	@echo "+-------+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

helloint: Makefile helloint.c
	@echo "+----------+"
	@echo "| helloint |"
	@echo "+----------+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

qsort: Makefile qsort.c
	@echo "+-------+"
	@echo "| qsort |"
	@echo "+-------+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

test_switch: Makefile test_switch.c
	@echo "+-------------+"
	@echo "| test_switch |"
	@echo "+-------------+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) --param case-values-threshold=1 -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 --param case-values-threshold=1 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

vecsum: Makefile vecsum.c
	@echo "+--------+"
	@echo "| vecsum |"
	@echo "+--------+"
	$(GCC) -S $(OPTFLAG) $@.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	${CHMOD} $@ $@.${OD}
#	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
#	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
#	${CHMOD} $@-noopt $@-noopt.${OD}

clean:
	${RM} *.s *.o *.so *.bak *.od
	${RM} gcd hello helloint qsort test_switch vecsum 
#	${RM} gcd-noopt hello-noopt qsort-noopt test_switch-noopt vecsum-noopt 