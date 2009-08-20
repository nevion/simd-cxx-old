#ifndef AC_SIMD_SIMD_HPP_
#define AC_SIMD_SIMD_HPP_

#include <simd/config.hpp>
#include <simd/traits.hpp>
#include <simd/runtime.hpp>
#include <simd/reader.hpp>
#include <simd/writer.hpp>
#include <simd/waitset.hpp>

namespace simd {
const std::string& retcode2string(::DDS::ReturnCode_t rc);
}

#endif /* AC_SIMD_SIMD_HPP_ */
