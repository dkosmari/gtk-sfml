#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([gtk-sfml], [0.4], [https://github.com/dkosmari/gtk-sfml])
AC_CONFIG_SRCDIR([src/DrawingArea.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


AC_LANG([C++])


PKG_INSTALLDIR


# Checks for libraries.

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])
PKG_CHECK_MODULES([SFML], [sfml-graphics])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_ENABLE([examples],
              [AS_HELP_STRING([--disable-examples],
                              [Disable compilation of examples.])])

AM_CONDITIONAL([ENABLE_EXAMPLES], [ test "x$enable_examples" != "xno" ])
AS_IF([test "x$enable_examples" = xno],
            [AC_MSG_NOTICE([Examples will not be compiled.])])


AC_CONFIG_FILES([
        examples/Makefile
        gtk-sfml.pc
        gtk-sfml.spec
        include/Makefile
        Makefile
        src/Makefile
])
AC_OUTPUT
