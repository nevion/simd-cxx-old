#ifndef SIMD_OS_WINDOWS_HPP_
#define SIMD_OS_WINDOWS_HPP_

// Set this to 1 if you run on Windows
#define SIMD_ON_WINDOWS 1
#define WINDOWS_DLL_EXPORT __declspec(dllexport)
#define SIMD_EXPORT WINDOWS_DLL_EXPORT

#endif /* SIMD_OS_WINDOWS_HPP_ */