// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_UTIL_ASSERTION_HH
# define HPP_UTIL_ASSERTION_HH
# include <boost/scope_exit.hpp>

# include <hpp/util/config.hh>
# include <hpp/util/exception.hh>

// If debug mode is disabled and assertions are not already
// disabled, disable them automatically.
# if (defined HPP_DEBUG) && (!defined HPP_ENABLE_ASSERTIONS)
#  define HPP_ENABLE_ASSERTIONS
# endif // (!defined HPP_DEBUG) && (!defined HPP_ENABLE_ASSERTIONS)

namespace hpp
{
  HPP_MAKE_EXCEPTION (HPP_UTIL_DLLAPI, AssertionError);
} // end of namespace hpp.

/// \brief Define HPP_ASSERT.
///
/// Throw an ::hpp::AssertionError if macro argument evaluates to
/// false.
# ifdef HPP_ENABLE_ASSERTIONS
#  define HPP_ASSERT(CONDITION)					\
  do {								\
    bool _x = (CONDITION);					\
    if (!_x)							\
      HPP_THROW_EXCEPTION					\
	(::hpp::AssertionError,					\
	 #CONDITION " evaluates to false");			\
  } while (0)
# else
#  define HPP_ASSERT(CONDITION)
# endif // HPP_ENABLE_ASSERTIONS

/// \brief Define macro for precondition checking.
# define HPP_PRECONDITION(CONDITION) HPP_ASSERT (CONDITION)

/// \brief Define macro for postcondition checking.
///
/// This macro allows an assertion to be done whenever a
/// scope is exited.
///
/// This macro takes two arguments: the condition which should
/// be evaluated and a list of captured variables.
/// All variables used in the condition must be in this list.
///
/// They can either be copied or taken by reference:
/// HPP_POSTCONDITION (a == 3, (a))
/// ...checks that a is equal to three and copy the variable a
/// when HPP_POSTCONDITION is called.
///
/// HPP_POSTCONDITION (a == 3, (&a))
/// ...takes a by reference and evaluated its final value (when
/// the scope is exited).
///
/// See Boost.ScopeExit for more details.
# define HPP_POSTCONDITION(CONDITION, CAPTURED_VARIABLES)	\
  BOOST_SCOPE_EXIT(CAPTURED_VARIABLES)				\
  {								\
    HPP_ASSERT (CONDITION);					\
  } BOOST_SCOPE_EXIT_END					\
  struct _e_n_d__w_i_t_h__s_e_m_i_c_o_l_o_n



#endif //! HPP_UTIL_ASSERTION_HH
