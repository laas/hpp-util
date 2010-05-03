// Copyright (C) 2010 by Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>
#include <boost/format.hpp>

#include "hpp/util/exception.hh"

namespace hpp
{
  Exception::Exception (const std::string& message,
			const std::string& file,
			unsigned line) throw ()
    : std::exception (),
      message_ (message),
      file_ (file),
      line_ (line)
  {}

  Exception::~Exception () throw ()
  {}

  Exception::Exception (const Exception& exception) throw ()
    : std::exception (),
      message_ (exception.message_),
      file_ (exception.file_),
      line_ (exception.line_)
  {}

  Exception&
  Exception::operator= (const Exception& exception) throw ()
  {
    if (&exception == this)
      return *this;

    message_ = exception.message_;
    file_  = exception.file_;
    line_  = exception.line_;
    return *this;
  }

  const char*
  Exception::what () const throw ()
  {
    //FIXME: display line and file too.
    return message_.c_str ();
  }

  std::ostream&
  Exception::print (std::ostream& o) const throw ()
  {
    using boost::format;
    o << (format ("%1%:%2%: %3%") % file_ % line_ % message_);
    return o;
  }


  std::ostream&
  operator<< (std::ostream& o, const Exception& exception)
  {
    exception.print (o);
    return o;
  }

} // end of namespace hpp.
