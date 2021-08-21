# src/Makefile.am


AM_CXXFLAGS = -Wall -Wextra -Werror


AM_CPPFLAGS = \
	$(GTKMM_CFLAGS) \
	$(SFML_CFLAGS)


lib_LTLIBRARIES = libgtk-sfml.la


libgtk_sfmldir = $(includedir)/gtk-sfml
libgtk_sfml_HEADERS = DrawingArea.hpp


libgtk_sfml_la_SOURCES = \
	DrawingArea.cpp \
	priv-utils.cpp priv-utils.hpp


libgtk_sfml_la_LIBADD = \
	$(GTKMM_LIBS) \
	$(SFML_LIBS)



.PHONY: company

company: compile_flags.txt

compile_flags.txt: Makefile
	echo "$(AM_CPPFLAGS) $(CPPFLAGS) $(DEFS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
