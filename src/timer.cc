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

#include <iostream>
//#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>

#include "hpp/util/timer.hh"

namespace hpp
{
  namespace debug
  {
    Timer::Timer (bool autoStart)
      : start_ (),
	end_ ()
    {
      if (autoStart)
	start ();
    }

    Timer::Timer (const Timer& timer)
      : start_ (timer.start_),
	end_ (timer.end_)
    {}

    Timer&
    Timer::operator= (const Timer& timer)
    {
      if (this == &timer)
	return *this;
      start_ = timer.start_;
      end_ = timer.end_;
      return *this;
    }

    Timer::~Timer ()
    {}

    const Timer::ptime&
    Timer::start ()
    {
      return start_ = boost::posix_time::microsec_clock::universal_time ();
    }

    const Timer::ptime&
    Timer::stop ()
    {
      return end_ = boost::posix_time::microsec_clock::universal_time ();
    }

    const Timer::ptime&
    Timer::getStart () const
    {
      return start_;
    }

    const Timer::ptime&
    Timer::getStop () const
    {
      return end_;
    }

    Timer::time_duration
    Timer::duration () const
    {
      time_period duration (start_, end_);
      return duration.length ();
    }

    std::ostream&
    Timer::print (std::ostream& o) const
    {
      using boost::format;
      return o <<
	(format
	 ("timer started at ``%1%'' and ended at ``%2%'' (elapsed time ``%3%''")
	 % start_ % end_ % duration ());
    }
  } // end of namespace debug
} // end of namespace hpp
