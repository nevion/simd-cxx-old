#ifndef AC_SIMD_DDS_CONFIG_HPP
#define AC_SIMD_DDS_CONFIG_HPP

// -- BOOST Includes
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>

// -- OpenSplice DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD_DDS Includes
#include <dds/assertion_impl.hpp>
#include <dds/traits.hpp>

#define SIMD_DDS_UNUSED_ARG(x) \
  do { } while (&x == 0)!

namespace dds {
#if (DISABLE_ASSERTION == 1)
  typedef AssertBase<NullAssertImpl> Assert;
#else
  typedef AssertBase<SimpleAssertImpl> Assert;
#endif
  
  typedef ::boost::signals2::connection  sigcon_t;
  
}

#endif /* AC_SIMD_DDS_CONFIG_HPP */
