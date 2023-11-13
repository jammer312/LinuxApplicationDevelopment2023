#!/usr/bin/env bash

md5Target="`echo -n 123 | md5sum | cut -f 1 -d ' '`"
md5Out="`echo -n 'md5 "123' | ./rhasher | tail -n 1`"

test x$md5Target == x$md5Out

md5Target="`md5sum Makefile | cut -f 1 -d ' '`"
md5Out="`echo -n 'md5 Makefile' | ./rhasher | tail -n 1`"

test x$md5Target == x$md5Out

sha1Target="`echo -n 123 | sha1sum | cut -f 1 -d ' '`"
sha1Out="`echo -n 'sha1 "123' | ./rhasher | tail -n 1`"

test x$sha1Target == x$sha1Out

sha1Target="`sha1sum Makefile | cut -f 1 -d ' '`"
sha1Out="`echo -n 'sha1 Makefile' | ./rhasher | tail -n 1`"

test x$sha1Target == x$sha1Out
