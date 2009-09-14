#ifndef AC_SIMD_CONFIG_HPP
#define AC_SIMD_CONFIG_HPP

// -- OpenSplice DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD Includes
#include <simd/assertion_impl.hpp>


#define SIMD_UNUSED_ARG(x) \
  do { } while (&x == 0)!

namespace simd {
#if (DISABLE_ASSERTION == 1)
  typedef AssertBase<NullAssertImpl> Assert;
#else
  typedef AssertBase<SimpleAssertImpl> Assert;
#endif
}

#endif /* AC_SIMD_CONFIG_HPP */
