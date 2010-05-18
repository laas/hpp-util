# Don't expend macros beginning by JRL_.
m4_pattern_forbid([^JRL_])
AC_PREREQ([2.63])

## --------------------- ##
## Package configuration ##
## --------------------- ##
AC_INIT([hpp-util],
        [m4_esyscmd(build-aux/git-version-gen .tarball-version)],
	[hpp@laas.fr],
	[hpp-util])

# Auxiliary files.
AC_CONFIG_AUX_DIR([build-aux])

# Automake.
AM_INIT_AUTOMAKE([1.9.6 dist-bzip2 -Wall nostdinc])

# Check configure is called properly.
AC_CONFIG_SRCDIR([src/debug.cc])

## ------------- ##
## C++ compiler  ##
## ------------- ##

# Search for a C++ compiler.
AC_LANG([C++])
AC_PROG_CXX

# Speed-up compilation.
if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -pipe"
fi

# Customize warnings.
JRL_CXX_WARNINGS([[-Wall],
                   [-Wcast-align],
                   [-Wcast-qual],
                   [-Wformat],
                   [-Wmissing-prototypes],
                   [-Wstrict-prototypes],
                   [-Wwrite-strings],
                   [-Wbad-function-cast],
                   [-Wmissing-declarations],
                   [-Wnested-externs]])

# Macros are stored in build-aux.
AC_CONFIG_MACRO_DIR([build-aux])

## ------------------- ##
## Additionnal tools.  ##
## ------------------- ##

# Search for misc. common tools.
AC_PROG_MKDIR_P
AC_PROG_SED

# Search for Doxygen.
JRL_PROG_DOXYGEN

# Search for Libtool.
LT_INIT([win32-dll])

# Search for Boost.
BOOST_REQUIRE([1.34])
BOOST_FILESYSTEM

BOOST_STRING
BOOST_SYSTEM #FIXME: required?


# Generate ``config.hh'' header file.
AC_SUBST([PACKAGE_CPPNAME],
 [`echo "$PACKAGE_TARNAME" \
  | tr '@<:@:lower:@:>@' '@<:@:upper:@:>@' | sed 's/-/_/g'`])
AC_CONFIG_FILES([include/hpp/util/config.hh])
AC_CONFIG_FILES([include/hpp/util/version.hh])

## ------------ ##
## Test-suite.  ##
## ------------ ##

AC_CONFIG_TESTDIR([tests])
AM_MISSING_PROG([AUTOM4TE], [autom4te])


## ------------ ##
## Pkg-config.  ##
## ------------ ##

AC_SUBST([PKGCONFIG_DESCRIPTION], ['HPP utilities'])
AC_SUBST([PKGCONFIG_URL], [])
AC_SUBST([PKGCONFIG_REQUIRES], [`echo "$PKGCONFIG_REQUIRES" | sed 's/, $//'`])
AC_SUBST([PKGCONFIG_CONFLICTS], [])
AC_SUBST([PKGCONFIG_LIBS], [-lhpp-util])
AC_SUBST([PKGCONFIG_CFLAGS], [])

## -------------- ##
## Write output.  ##
## -------------- ##

# Create config.h
AC_CONFIG_HEADERS([config.h])

# Create Makefiles.
AC_CONFIG_FILES([
  Makefile
   include/Makefile
   src/Makefile
   doc/Makefile
   tests/Makefile
    tests/atlocal
    tests/package.m4
])

# Write files.
AC_OUTPUT
