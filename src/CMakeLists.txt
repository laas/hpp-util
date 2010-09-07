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

# Check for unistd.h presence.
INCLUDE(CheckIncludeFiles)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
IF(${HAVE_UNISTD_H})
  ADD_DEFINITIONS(-DHAVE_UNISTD_H)
ENDIF(${HAVE_UNISTD_H})

# The shared library is being built right now.
# Required for dllimport/dllexport mechanisms in
# the generated header config.hh.
ADD_DEFINITIONS(-DBUILDING_HPP_UTIL)

# Define logging directory location.
ADD_DEFINITIONS(-DHPP_LOGGINGDIR="${CMAKE_INSTALL_PREFIX}/var/log")

# Default include directories.
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${CMAKE_CURRENT_BINARY_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Compile hpp-util library.
ADD_LIBRARY(hpp-util
  SHARED
  debug.cc
  exception.cc
  indent.cc
  timer.cc
  version.cc
)
INSTALL(TARGETS hpp-util DESTINATION lib)
