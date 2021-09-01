# examples/Makefile.am


EXTRA_DIST = LiberationSans-Regular.ttf


AM_CXXFLAGS = -Wall -Werror


AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	$(GTKMM_CFLAGS) \
	$(SFML_CFLAGS) \
	-DDEMO_FONT=\"$(abs_srcdir)/LiberationSans-Regular.ttf\" \
	-DNOT_INSTALLED


LDADD = \
	$(top_builddir)/src/libgtk-sfml.la \
	$(GTKMM_LIBS) \
	$(SFML_LIBS)


noinst_PROGRAMS = \
	demo-application-window \
	demo-drawing-area \
	demo-dvd-screensaver \
	demo-window \
	demo-hello-world \
	test-events-drawing-area \
	test-events-sfml


demo_application_window_SOURCES = application-window.cpp


demo_drawing_area_SOURCES = drawing-area.cpp


demo_dvd_screensaver_SOURCES = dvd-screensaver.cpp


demo_window_SOURCES = window.cpp


demo_hello_world_SOURCES = hello-world.cpp


test_events_drawing_area_SOURCES = \
	events-drawing-area.cpp \
	utils.cpp utils.hpp


test_events_sfml_SOURCES = \
	events-sfml.cpp \
	utils.cpp utils.hpp


.PHONY: company

company: compile_flags.txt

compile_flags.txt: Makefile
	echo "$(AM_CPPFLAGS) $(CPPFLAGS) $(DEFS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
