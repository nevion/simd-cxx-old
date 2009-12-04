#ifndef AC_SIMD_DDS_SIMD_HPP_
#define AC_SIMD_DDS_SIMD_HPP_

#include <dds/config.hpp>
#include <dds/traits.hpp>
#include <dds/runtime.hpp>
#include <dds/reader.hpp>
#include <dds/writer.hpp>
#include <dds/waitset.hpp>

namespace dds {
const std::string& retcode2string(::DDS::ReturnCode_t rc);
}

#endif /* AC_SIMD_DDS_SIMD_HPP_ */
