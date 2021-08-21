# examples/Makefile.am


EXTRA_DIST = LiberationSans-Regular.ttf


AM_CXXFLAGS = -Wall -Werror


AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	$(GTKMM_CFLAGS) \
	$(SFML_CFLAGS) \
	-DSRCDIR=\"$(abs_srcdir)\"


LDADD = \
	$(top_builddir)/src/libgtk-sfml.la \
	$(GTKMM_LIBS) \
	$(SFML_LIBS)


noinst_PROGRAMS = \
	hello-world \
	event-test


hello_world_SOURCES = hello-world.cpp


event_test_SOURCES = event-test.cpp


.PHONY: company

company: compile_flags.txt

compile_flags.txt: Makefile
	echo "$(AM_CPPFLAGS) $(CPPFLAGS) $(DEFS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
