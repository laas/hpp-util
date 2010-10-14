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

SET(PROJECT_NAME hpp-util)
SET(PROJECT_VERSION 0.3)
SET(PROJECT_DESCRIPTION "Debugging tools for the HPP project.")
SET(PROJECT_URL "http://github.com/laas/hpp-util")

SETUP_PROJECT()

SET(PKG_CONFIG_LIBS ${PKG_CONFIG_LIBS} "-lhpp-util")

# Search for Boost.
FIND_PACKAGE(Boost 1.34 COMPONENTS filesystem system)

SET(${PROJECT_NAME}_HEADERS
  include/hpp/util/assertion.hh
  include/hpp/util/debug.hh
  include/hpp/util/deprecated.hh
  include/hpp/util/exception.hh
  include/hpp/util/indent.hh
  include/hpp/util/portability.hh
  include/hpp/util/timer.hh
  include/hpp/util/version.hh
)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
