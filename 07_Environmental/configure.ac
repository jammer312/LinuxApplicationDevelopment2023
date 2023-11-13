#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [example@example.com])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC AM_INIT_AUTOMAKE

AC_ARG_WITH([readline],
	[AS_HELP_STRING([--without-readline],
	[disable support for readline])],
    [],
    [with_readline=check])

# Checks for libraries.
AS_IF([test "x$with_readline" != xno],
    [AC_CHECK_LIB([readline], [readline], [], [AC_MSG_FAILURE([readline test failed (--without-readline to disable)])])], [])

AC_CHECK_LIB([rhash], [rhash_file], [], [
  AC_MSG_ERROR([Unable to find librhash])
])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
