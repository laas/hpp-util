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

#include "config.h"

#include <cassert>
#include <iostream>
#include <hpp/util/exception.hh>

#include "common.hh"


int run_test ();

int run_test ()
{
  ::hpp::Exception exception ("put your error here",
			      "filename",
			      0);
  std::cout << exception << std::endl;

  try
    {
      HPP_THROW_EXCEPTION ("this error should be catched");
      assert (0);
    }
  catch (::hpp::Exception& exception)
    {
      std::cout << exception << std::endl;
    }

  return 0;
}

GENERATE_TEST ()
