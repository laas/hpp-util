// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include "hpp/util/version.hh"

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace hpp
{
  namespace util
  {
    const char* version = PACKAGE_VERSION;

    int checkVersion (const char* header_version)
    {
      std::vector<std::string> headerVersion;
      std::vector<std::string> libraryVersion;

      boost::split (headerVersion, header_version, boost::is_any_of("."));
      boost::split (libraryVersion, version, boost::is_any_of("."));

      long unsigned s = std::max (headerVersion.size (),
				  libraryVersion.size ());
      headerVersion.resize (s);
      libraryVersion.resize (s);

      assert (headerVersion.size () == libraryVersion.size ());

      for (long unsigned i = 0; i < s; ++i)
	{
	  if (headerVersion != libraryVersion)
	    return (headerVersion > libraryVersion) ? -1 : 1;
	}
      return 0;
    }
  } // end of namespace util.
} // end of namespace hpp.
