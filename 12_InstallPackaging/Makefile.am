SUBDIRS = src tests

install-exec-local:
	mv $(DESTDIR)$(bindir)/demo $(DESTDIR)$(bindir)/demo.orig
	echo "LD_LIBRARY_PATH=$(DESTDIR)$(libdir) $(DESTDIR)$(bindir)/demo.orig" > $(DESTDIR)$(bindir)/demo
	chmod +x $(DESTDIR)$(bindir)/demo

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov
