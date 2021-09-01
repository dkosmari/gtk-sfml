#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.70])
AC_INIT([libgtk-sfml], [0.2], [])
AC_CONFIG_SRCDIR([src/DrawingArea.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE
LT_INIT([disable-static])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


AX_CXX_COMPILE_STDCXX_17([noext])

AC_LANG([C++])

PKG_INSTALLDIR


# Checks for libraries.

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])
PKG_CHECK_MODULES([SFML], [sfml-graphics])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
        examples/Makefile
        libgtk-sfml.pc
        libgtk-sfml.spec
        Makefile
        src/Makefile
])
AC_OUTPUT
