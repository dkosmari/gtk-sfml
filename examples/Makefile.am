# examples/Makefile.am


EXTRA_DIST = LiberationSans-Regular.ttf


AM_CXXFLAGS = -Wall -Wextra


AM_CPPFLAGS = \
	$(GTKMM_CFLAGS) \
	$(SFML_CFLAGS) \
	-I$(top_srcdir)/include


LDADD = \
	$(top_builddir)/src/libgtk-sfml.la \
	$(GTKMM_LIBS) \
	$(SFML_LIBS)


# this will pack a .ttf font into an object to be linked with the program.
SUFFIXES = .ttf

.ttf.o:
	$(LD) --format binary --relocatable -z noexecstack $< -o $@


if ENABLE_EXAMPLES


noinst_PROGRAMS = \
	demo-application-window \
	demo-drawing-area \
	demo-dvd-screensaver \
	demo-window \
	demo-hello-world \
	test-events-drawing-area \
	test-events-sfml

# common sources for all examples
COMMON = font.hpp LiberationSans-Regular.ttf


demo_application_window_SOURCES = application-window.cpp $(COMMON)


demo_drawing_area_SOURCES = drawing-area.cpp $(COMMON)


demo_dvd_screensaver_SOURCES = dvd-screensaver.cpp $(COMMON)


demo_window_SOURCES = window.cpp $(COMMON)


demo_hello_world_SOURCES = hello-world.cpp $(COMMON)


test_events_drawing_area_SOURCES = \
	events-drawing-area.cpp \
	utils.cpp utils.hpp \
	$(COMMON)


test_events_sfml_SOURCES = \
	events-sfml.cpp \
	utils.cpp utils.hpp \
	$(COMMON)


endif ENABLE_EXAMPLES


.PHONY: company

company: compile_flags.txt

compile_flags.txt: Makefile
	echo "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
