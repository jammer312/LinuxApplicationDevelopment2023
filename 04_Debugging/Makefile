GENERATES = range
TRASH = *.o *~ *.out test1 test2

CFLAGS = -Wall -O0 -g

all: $(GENERATES) test

range: range.o

test: test1 test2

test1: range
	gdb -q range -x scenario1 2>/dev/null | grep "@@@" >test1
	cmp test1 scenario1-target

test2: range
	gdb -q range -x scenario2 2>/dev/null | grep "@@@" >test2
	cmp test2 scenario2-target

cleantmp:
	rm -f $(TRASH)

clean: cleantmp
	rm -f $(GENERATES)
