include $(top_srcdir)/build-aux/init.mk

# Define logging directory.
loggingdir = $(DESTDIR)$(localstatedir)/log

# Add available warnings flags.
AM_CXXFLAGS += $(WARNING_CXXFLAGS)

# Add Boost.Filesystem linker flags.
AM_LDFLAGS += $(BOOST_FILESYSTEM_LDFLAGS)

# Make sure all symbols are defined.
AM_LDFLAGS += -no-undefined

# Add dependencies CPPFLAGS.
AM_CPPFLAGS += 					\
	-DBUILDING_HPP_UTIL			\
	-DHPP_LOGGINGDIR=\"$(loggingdir)\"	\
	$(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libhpp-util.la

libhpp_util_la_SOURCES = 			\
	debug.cc				\
	exception.cc				\
	indent.cc				\
	timer.cc

libhpp_util_la_LIBADD = 			\
	$(BOOST_FILESYSTEM_LIBS)		\
	$(BOOST_SYSTEM_LIBS)
