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

#ifndef HPP_UTIL_TIMER_HH
# define HPP_UTIL_TIMER_HH

# include "boost/date_time/posix_time/posix_time_types.hpp"

# ifdef HPP_ENABLE_BENCHMARK
#  include <boost/date_time/posix_time/posix_time.hpp>
# endif // HPP_ENABLE_BENCHMARK

# include <hpp/util/config.hh>
# include <hpp/util/debug.hh>

namespace hpp
{
  namespace debug
  {
    class Timer
    {
    public:
      typedef boost::posix_time::ptime ptime;
      typedef boost::posix_time::time_duration time_duration;
      typedef boost::posix_time::time_period time_period;

      explicit Timer (bool autoStart = false);
      Timer (const Timer&);
      Timer& operator= (const Timer&);
      ~Timer ();

      const ptime& start ();
      const ptime& stop ();
      time_duration duration () const;

      const ptime& getStart () const;
      const ptime& getStop () const;

      std::ostream& print (std::ostream&) const;
    private:
      ptime start_;
      ptime end_;
    };

# ifdef HPP_ENABLE_BENCHMARK

#  define hppStartBenchmark(ID)			\
    hppDout (benchmark, #ID << ": start");	\
    ::hpp::debug::Timer _##ID##_timer_ (true)

#  define hppStopBenchmark(ID)			\
    do {					\
      _##ID##_timer_.stop ();			\
      hppDout (benchmark, #ID << ": stop");	\
    } while (0)

#  define hppDisplayBenchmark(ID)					\
    hppDout (benchmark, #ID << ": "<< _##ID##_timer_.duration ());

# else
#  define hppStartBenchmark(ID)
#  define hppStopBenchmark(ID)
#  define hppDisplayBenchmark(ID)
# endif // HPP_ENABLE_BENCHMARK

  } // end of namespace debug
} // end of namespace hpp

#endif // HPP_UTIL_TIMER_HH
