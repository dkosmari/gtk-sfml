# top Makefile.am

EXTRA_DIST = \
	bootstrap \
	gtk-sfml.pc.in \
	gtk-sfml.spec.in \
	README.md


SUBDIRS = src examples



pcfiledir = $(pkgconfigdir)
pcfile_DATA = gtk-sfml.pc



.PHONY: rpm


rpm: gtk-sfml.spec dist-gzip
	rpmbuild -ba --define="_sourcedir $(abs_top_srcdir)" $<

# [ -e $(RPM_TARBALL_NAME) ] || \
# 	$(LN_S) $(PWD)/$(TARBALL_NAME) $(RPM_TARBALL_NAME)
