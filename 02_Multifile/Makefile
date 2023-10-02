GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ *.out

CFLAGS = -Wall

all: $(GENERATES) test

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	$(LINK.o) prog.o $(LOADLIBES) $(LDLIBS) -L. -l:liboutput_static.a -o $@

prog-so: prog.o liboutput.so
	$(LINK.o) prog.o $(LOADLIBES) $(LDLIBS) -L. -l:liboutput.so -o $@

README: prog
	./$< 2> $@

test: test1 test2 test3

test1: prog prog-a prog-so
	./prog 2>&1 | sed 's|\./prog|./prog|g' >test1.out
	./prog-a 2>&1 | sed 's|\./prog-a|./prog|g' >test1.a.out
	LD_LIBRARY_PATH=`pwd` ./prog-so 2>&1 | sed 's|\./prog-so|./prog|g' >test1.so.out
	cmp test1.out test1.a.out && cmp test1.a.out test1.so.out && cmp test1.so.out test1.out
test2: prog prog-a prog-so
	./prog 1 2>&1 | sed 's|\./prog|./prog|g' >test2.out
	./prog-a 1 2>&1 | sed 's|\./prog-a|./prog|g' >test2.a.out
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2>&1 | sed 's|\./prog-so|./prog|g' >test2.so.out
	cmp test2.out test2.a.out && cmp test2.a.out test2.so.out && cmp test2.so.out test2.out
test3: prog prog-a prog-so
	./prog 1 2 3 2>&1 | sed 's|\./prog|./prog|g' >test3.out
	./prog-a 1 2 3 2>&1 | sed 's|\./prog-a|./prog|g' >test3.a.out
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 2>&1 | sed 's|\./prog-so|./prog|g' >test3.so.out
	cmp test3.out test3.a.out && cmp test3.a.out test3.so.out && cmp test3.so.out test3.out

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	$(LINK.c) -shared $^ $(LOADLIBES) $(LDLIBS) -o $@

fun.o: outlib.h
prog.o: outlib.h

%.o: %.c
	$(COMPILE.c) -fPIC $(OUTPUT_OPTION) $<

cleantmp:
	rm -f $(TRASH)

clean: cleantmp
	rm -f $(GENERATES)
