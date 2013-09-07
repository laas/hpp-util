hpp-util
========

[![Build Status](https://travis-ci.org/laas/hpp-util.png)](https://travis-ci.org/laas/hpp-util)
[![Coverage Status](https://coveralls.io/repos/laas/hpp-util/badge.png?branch=master)](https://coveralls.io/r/laas/hpp-util?branch=master)

This package gathers technical tools for the HPP project. Features include:
 - debugging
 - benchmarks

Setup
-----

To compile this package, it is recommended to create a separate build
directory:

    mkdir _build
    cd _build
    cmake [OPTIONS] ..
    make install

Please note that CMake produces a `CMakeCache.txt` file which should
be deleted to reconfigure a package from scratch.


### Dependencies

The package depends on several packages which have to be available on
your machine.

 - System tools:
   - CMake (>=2.6)
   - pkg-config
   - usual compilation tools (GCC/G++, make, etc.)
