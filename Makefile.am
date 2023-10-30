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

TARBALL_NAME = $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz
RPM_TARBALL_NAME = $(HOME)/rpmbuild/SOURCES/$(TARBALL_NAME)

rpm: gtk-sfml.spec dist-gzip
	[ -e $(RPM_TARBALL_NAME) ] || \
		$(LN_S) $(PWD)/$(TARBALL_NAME) $(RPM_TARBALL_NAME)
	rpmbuild -ba $<

