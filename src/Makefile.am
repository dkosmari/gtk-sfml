# src/Makefile.am


AM_CXXFLAGS = -Wall -Wextra


AM_CPPFLAGS = \
	$(GTKMM_CFLAGS) \
	$(SFML_CFLAGS) \
	-I$(top_srcdir)/include


lib_LTLIBRARIES = libgtk-sfml.la


libgtk_sfml_la_SOURCES = \
	ApplicationWindow.cpp \
	DrawingArea.cpp \
	priv-methods.hpp \
	priv-utils.cpp priv-utils.hpp \
	Window.cpp


libgtk_sfml_la_LIBADD = \
	$(GTKMM_LIBS) \
	$(SFML_LIBS)



.PHONY: company

company: compile_flags.txt

compile_flags.txt: Makefile
	echo "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
