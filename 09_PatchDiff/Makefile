GENERATES = lab lab1 lab2 lab3
TRASH = *.o *~ *.out lab1.c lab2.c lab3.c

CFLAGS = -Wall -O0 -g

all: $(GENERATES) run

lab: lab.o
lab1: lab1.o
lab2: lab2.o
lab3: lab3.o

lab1.c: lab.c 0001-Define-Size.patch
	patch lab.c --input=0001-Define-Size.patch --output=lab1.c

lab2.c: lab.c 0002-Define-Chars.patch
	patch lab.c --input=0002-Define-Chars.patch --output=lab2.c

lab3.c: lab.c 0003-Define-Seed.patch
	patch lab.c --input=0003-Define-Seed.patch --output=lab3.c

run: lab lab1 lab2 lab3
	./lab
	./lab1 8
	./lab2 ' @' 5
	./lab3 12 '.#' 4

clean: cleantmp
	rm -f $(GENERATES)

cleantmp:
	rm -f $(TRASH)