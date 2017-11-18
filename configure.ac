AC_PREREQ([2.69])
AC_INIT([libnrf24lu1p], [0.1.0], [gherlein@herlein.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/tx-test/tx-test.c])
AC_CONFIG_HEADERS([config.h])
AC_C_INLINE
AM_INIT_AUTOMAKE



# Checks for programs.
AM_PROG_AR
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_LIBTOOL

# Checks for libraries.

PKG_CHECK_MODULES([USB], [libusb-1.0])
AC_SUBST([USB_CFLAGS])
AC_SUBST([USB_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

LT_INIT



AC_OUTPUT(Makefile 
          src/Makefile 
          src/lib/Makefile 
          src/tx-test/Makefile
          src/rx-test/Makefile
          src/sniff-test/Makefile)


