// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_DEPRECATED_HH
# define HPP_DEPRECATED_HH

// Define a suffix which can be used to tag a type, a function or a a
// variable as deprecated (i.e. it will emit a warning when using it).
//
// Tagging a function as deprecated:
//  void foo () HPP_DEPRECATED;
//
// Tagging a type as deprecated:
//  class Foo {};
//  typedef Foo Bar HPP_DEPRECATED;
//
// Tagging a variable as deprecated:
//  int a HPP_DEPRECATED = 0;
//
// The use of a macro is required as this is /not/ a standardized
// feature of C++ language or preprocessor, even if most of the
// compilers support it.
# ifdef __GNUC__
#  define HPP_DEPRECATED __attribute__ ((deprecated))
# else
#  ifdef _MSC_VER
#   define HPP_DEPRECATED __declspec (deprecated)
#  else
// If the compiler is not recognized, drop the feature.
#   define HPP_DEPRECATED /* nothing */
#  endif // __MSVC__
# endif // __GNUC__

#endif //! HPP_DEPRECATED_HH
