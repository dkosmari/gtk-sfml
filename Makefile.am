# top Makefile.am

ACLOCAL_AMFLAGS = -I m4


EXTRA_DIST = \
	bootstrap \
	libgtk-sfml.pc.in \
	libgtk-sfml.spec.in


SUBDIRS = src examples



pcfiledir = $(pkgconfigdir)
pcfile_DATA = libgtk-sfml.pc



.PHONY: rpm

TARBALL_NAME = $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz
RPM_TARBALL_NAME = $(HOME)/rpmbuild/SOURCES/$(TARBALL_NAME)

rpm: libgtk-sfml.spec dist-gzip
	[ -e $(RPM_TARBALL_NAME) ] || \
		$(LN_S) $(PWD)/$(TARBALL_NAME) $(RPM_TARBALL_NAME)
	rpmbuild -ba $<

