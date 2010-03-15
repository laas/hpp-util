// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, CNRS.
//
// This file is part of the hpp/walkfootplanner.
//
// hpp/walkfootplanner is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp/walkfootplanner is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp/walkfootplanner.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include "hpp/util/indent.hh"
#include "hpp/util/debug.hh"

#ifndef HPP_LOGGINGDIR
# error "Please define HPP_LOGGINGDIR to the default logging prefix."
#endif //! HPP_LOGGINGDIR

// Include unistd.h if available, otherwise use the dummy getpid
// function.
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#else
static int getpid ()
{
  return 0;
}
#endif // HAVE_UNISTD_H

namespace hpp
{
  namespace debug
  {

    /// \brief Environment variable used to change the logging
    /// directory.
    static const char* ENV_LOGGINGDIR = "HPP_LOGGINGDIR";

    namespace
    {
      HPP_UTIL_LOCAL void
      makeDirectory (const std::string& filename)
      {
	using namespace boost::filesystem;
	path pathname (filename);

	// FIXME: Boost 1.34.1 does not support the non-obsolete
	// equivalent of branch_path, parent_path, so bear with
	// it for now.
	std::string dirname = pathname.branch_path ().string ();

	boost::filesystem::create_directories (dirname);
      }
    }

    std::string
    getPrefix (const std::string& packageName)
    {
      std::string loggingPrefix;
      const char* env = getenv (ENV_LOGGINGDIR);

      if (env)
	loggingPrefix = env;
      else
	{
	  loggingPrefix = HPP_LOGGINGDIR;
	  if (!packageName.empty ())
	    {
	      loggingPrefix += '/';
	      loggingPrefix += packageName;
	    }
	}

      return loggingPrefix;
    }

    std::string
    getFilename (const std::string& filename,
		 const std::string& packageName)
    {
      std::string res (getPrefix (packageName));
      res += "/";
      res += filename;
      makeDirectory (res);
      return res;
    }

    std::ostream&
    Output::writePrefix (std::ostream& stream,
			 const Channel& channel,
			 char const* file,
			 int line,
			 char const* function)
    {
      stream
	<< channel.label () << ':'
	<< file << ':'
	<< line << ": ";
      return stream;
    }


    Channel::Channel (const char* label,
		      const subscribers_t& subscribers)
      : label_ (label),
	subscribers_ (subscribers)
    {}

    const char*
    Channel::label () const
    {
      return label_;
    }

    void
    Channel::write (char const* file,
		    int line,
		    char const* function,
		    const std::string& data)
    {
      BOOST_FOREACH (Output* o, subscribers_)
	if (o)
	  o->write (*this, file, line, function, data);
    }


    ConsoleOutput::ConsoleOutput ()
    {}

    void
    ConsoleOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::string& data)
    {
      writePrefix (std::cerr, channel, file, line, function);
      std::cerr << incindent << data << decindent << std::flush;
    }

    namespace
    {
      HPP_UTIL_LOCAL std::string
      makeLogFile (const JournalOutput& journalOutput)
      {
	makeDirectory (journalOutput.getFilename ());
	return journalOutput.getFilename ();
      }
    }

    JournalOutput::JournalOutput (std::string filename)
      : filename (filename),
	lastFunction (),
	stream (makeLogFile (*this).c_str ())
    {}

    // package name is set to ``hpp'' here so that
    // the journal can be shared between all hpp packages.
    // Splitting log into multiple files would make difficult
    // to track packages interactions.
    std::string
    JournalOutput::getFilename () const
    {
      static const std::string packageName = "hpp";

      boost::format fmter ("%1%.%2%.log");
      fmter % filename % getpid ();
      return debug::getFilename (fmter.str (), packageName);
    }

    void
    JournalOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::string& data)
    {
      if (lastFunction != function)
	{
	  if (!lastFunction.empty ())
	    {
	      writePrefix (stream, channel, file, line, function);
	      stream << "exiting " << lastFunction << iendl;
	    }

	  writePrefix (stream, channel, file, line, function);
	  stream << "entering " << function << iendl;
	  lastFunction = function;
	}

      writePrefix (stream, channel, file, line, function);
      stream << incindent << data << decindent << std::flush;
    }
  } // end of namespace debug.

} // end of namespace hpp.


// Global variables definitions.
#include <boost/assign/list_of.hpp>

namespace hpp
{
  namespace debug
  {
    using boost::assign::list_of;
    // Default output.
    ConsoleOutput console;
    JournalOutput journal ("journal");
    JournalOutput benchmarkJournal ("benchmark");

    // Default channels.
    Channel error ("ERROR", list_of<Output*> (&journal) (&console));
    Channel warning ("WARNING", list_of<Output*> (&journal) (&console));
    Channel notice ("NOTICE", list_of<Output*> (&journal) (&console));

    Channel info ("INFO", list_of<Output*> (&journal));

    Channel benchmark ("BENCHMARK", list_of<Output*> (&benchmarkJournal));
  } // end of namespace debug
} // end of namespace hpp
