#ifndef AC_SIMD_DDS_CONFIG_HPP
#define AC_SIMD_DDS_CONFIG_HPP

// #include <dds/osmacros.hpp>
//////////////////////////////////////////////////////////////////////////////
// Other  Macros
//////////////////////////////////////////////////////////////////////////////
#define SIMD_UNUSED_ARG(x) \
  do { } while (&x == 0);

//////////////////////////////////////////////////////////////////////////////
// SIMD LOG-specific Macros
//////////////////////////////////////////////////////////////////////////////
#define SIMD_LOGS_ALLOC 1
#define SIMD_LOGS_INFO 1
#define SIMD_ENABLE_LOGS 0
// -- C++ Includes
#if (SIMD_ENABLE_LOGS == 1)
#   include <iostream>
#else
#   include <string>
#endif 

enum {
  SIMD_ALLOC,
  SIMD_INFO,
  SIMD_WARNING,
  SIMD_ERROR,
  SIMD_UNSUPPORTED,
  __SIMD_LOG_TAG_NUM__ // This has to remain the last
};
extern const std::string SIMD_LOG_TAG[];

#if (SIMD_ENABLE_LOGS == 1)
#   define SIMD_LOG(what, str) std::cout << "SIMD[" << SIMD_LOG_TAG[what] <<"]>>" << str << std::endl
#else
#   define SIMD_LOG(what, str) 
#endif /* (SIMD_LOGS_ALLOC == 1) */


// -- BOOST Includes
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>

// -- OpenSplice DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD_DDS Includes
#include <dds/assertion_impl.hpp>
#include <dds/traits.hpp>

//////////////////////////////////////////////////////////////////////////////
// SIMD Assertions Configuration
//////////////////////////////////////////////////////////////////////////////
#define SIMD_HAS_ASSERTIONS 1

namespace dds {
#if (SIMD_HAS_ASSERTIONS == 0)
  typedef AssertBase<NullAssertImpl> Assert;
#else
  typedef AssertBase<SimpleAssertImpl> Assert;
#endif
  typedef ::boost::signals2::connection  sigcon_t;
}



#endif /* AC_SIMD_DDS_CONFIG_HPP */
