#ifndef AC_SIMD_CONFIG_HPP
#define AC_SIMD_CONFIG_HPP

#include <simd/assertion_impl.hpp>

namespace simd {
#if (DISABLE_ASSERTION == 1)
  typedef AssertBase<NullAssertImpl> Assert;
#else
  typedef AssertBase<SimpleAssertImpl> Assert;
#endif
}

#endif /* AC_SIMD_CONFIG_HPP */
