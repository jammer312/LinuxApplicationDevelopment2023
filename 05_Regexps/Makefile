GENERATES = esub
TRASH = *.o *~ *.out test1.* test2.* test3.* test4.*

CFLAGS = -Wall -O0 -g

all: $(GENERATES) test

esub: esub.o

test: test1 test2 test3 test4

test1: esub
	./esub '1(2(3)?)?' '\0\\A\1B\2' '123' >test1.esub 2>test1.esub.err
	echo -n '123' | sed -E 's/1(2(3)?)?/\0\\A\1B\2/' >test1.sed 2>test1.sed.err
	(test -s test1.esub.err && test -s test1.sed.err) || (test ! -s test1.esub.err && test ! -s test1.sed.err && cmp test1.esub test1.sed)

test2: esub
	./esub '1(2(3)?)?' '\0\\A\1B\2' '13' >test2.esub 2>test2.esub.err
	echo -n '13' | sed -E 's/1(2(3)?)?/\0\\A\1B\2/' >test2.sed 2>test2.sed.err
	(test -s test2.esub.err && test -s test2.sed.err) || (test ! -s test2.esub.err && test ! -s test2.sed.err && cmp test2.esub test2.sed)

test3: esub
	-./esub '1(2(3)?)?' '\0\\A\1B\2C\3' '13' >test3.esub 2>test3.esub.err
	-echo -n '13' | sed -E 's/1(2(3)?)?/\0\\A\1B\2C\3/' >test3.sed 2>test3.sed.err
	(test -s test3.esub.err && test -s test3.sed.err) || (test ! -s test3.esub.err && test ! -s test3.sed.err && cmp test3.esub test3.sed)

test4: esub
	-./esub '*' '' '13' >test4.esub 2>test4.esub.err
	-echo -n '13' | sed -E 's/*//' >test4.sed 2>test4.sed.err
	(test -s test4.esub.err && test -s test4.sed.err) || (test ! -s test4.esub.err && test ! -s test4.sed.err && cmp test4.esub test4.sed)

cleantmp:
	rm -f $(TRASH)

clean: cleantmp
	rm -f $(GENERATES)
