#ifndef SIMD_OS_MACROS_HPP_
#define SIMD_OS_MACROS_HPP_

#ifdef WIN32
#include <dds/os-win32.hpp>
#else
#include <dds/os-linux.hpp>
#endif

#endif /* SIMD_OS_MACROS_HPP_ */