#ifndef SIMD_OS_WINDOWS_HPP_
#define SIMD_OS_WINDOWS_HPP_

#define WINDOWS_DLL_EXPORT __declspec(dllexport)
#define WINDOWS_DLL_IMPORT __declspec(dllimport)

#ifdef SIMD_API_BUILD
#define SIMD_API WINDOWS_DLL_EXPORT
#else
#define SIMD_API WINDOWS_DLL_IMPORT
#endif

#endif /* SIMD_OS_WINDOWS_HPP_ */