#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([nss_me], m4_esyscmd_s([git describe --tags --always --dirty]), [lenaic@lhuard.fr])
AC_CONFIG_SRCDIR([src/nss-me.c])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror dist-bzip2 dist-xz subdir-objects])
AM_PROG_AR
LT_INIT
AM_SILENT_RULES([yes])
AC_SUBST([AM_CFLAGS], ['-pipe -Wall -Wextra -Werror'])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AX_GCC_VAR_ATTRIBUTE([unused])
AC_TYPE_UID_T
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
