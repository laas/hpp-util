# Copyright (C) 2010 Florent Lamiraux, Thomas Moulard, JRL, CNRS/AIST.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)

SET(PROJECT_NAME hpp-util)
SET(PROJECT_DESCRIPTION "Debugging tools for the HPP project.")
SET(PROJECT_URL "http://github.com/laas/hpp-util")

SET(CXX_DISABLE_WERROR 1)

SETUP_PROJECT()

PKG_CONFIG_APPEND_LIBS("hpp-util")

# Search for Boost.
SET(BOOST_COMPONENTS filesystem system)
SEARCH_FOR_BOOST()


SET(${PROJECT_NAME}_HEADERS
  include/hpp/util/assertion.hh
  include/hpp/util/debug.hh
  include/hpp/util/doc.hh
  include/hpp/util/exception.hh
  include/hpp/util/indent.hh
  include/hpp/util/kitelab.hh
  include/hpp/util/portability.hh
  include/hpp/util/timer.hh
  include/hpp/util/version.hh
)

# Add Boost path to include directories.
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
