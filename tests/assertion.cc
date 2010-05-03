// Copyright (C) 2010 by Thomas Moulard.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

// Make sure assertions are enabled (otherwise this test does not make
// sense).
#ifndef HPP_ENABLE_ASSERTIONS
# define HPP_ENABLE_ASSERTIONS
#endif // !HPP_ENABLE_ASSERTIONS

#include "config.h"

#include <cassert>
#include <iostream>
#include <hpp/util/assertion.hh>

#include "common.hh"

int run_test ();
int my_plus_function (int a, int b);
int my_broken_plus_function (int a, int b);

int my_plus_function (int a, int b)
{
  // This algorithm does not work with negative numbers.
  HPP_PRECONDITION (a >= 0);
  HPP_PRECONDITION (b >= 0);

  int res = 0;

  // This algorithm should compute a + b.
  HPP_POSTCONDITION (res == a + b, (&res) (a) (b));

  res = b;
  while (a > 0)
    --a, ++res;
  return res;
}

int my_broken_plus_function (int a, int b)
{
  // This algorithm does not work with negative numbers.
  HPP_PRECONDITION (a >= 0);
  HPP_PRECONDITION (b >= 0);

  int res = 0;

  // This algorithm should compute a + b.
  HPP_POSTCONDITION (res == a + b, (&res) (a) (b));

  res = b; // This is wrong.
  return res;
}

int run_test ()
{
  // Assertion.
  try
    {
      int i = 4;
      HPP_ASSERT (i > 2);
      HPP_ASSERT (i < 3);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  // Good calls.
  my_plus_function (4, 5);
  my_plus_function (7, 9);

  // Check for precondition failure.
  try
    {
      my_plus_function (-2, 5);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  // Check for postcondition failure.
  try
    {
      my_broken_plus_function (3, 5);
    }
  catch (::hpp::AssertionError& assertionError)
    {
      std::cout << assertionError << std::endl;
    }

  return 0;
}

GENERATE_TEST ()
