CFLAGS = -ansi -pedantic -Wall -Wextra
if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
libbuf_la_SOURCES = libbuf.c
include_HEADERS = libbuf.h

bin_PROGRAMS = demo
demo_SOURCES = demo.c
demo_LDADD = libbuf.la

gcov:
	gcov -o .libs libbuf -tf | grep -E "Function|Lines executed"
