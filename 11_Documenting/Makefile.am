SUBDIRS = src po

@DX_RULES@

doxygen-doc/man/man1/guesser.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guesser.1

http:	doxygen-doc
	python3 -m http.server --directory $</html