#pragma once

/// @file
/// Commonly used typedefs for integer, floating-point, and boolean types.
/// Contains platform detection and a DLL Exporting/Importing macro.

/// Unsigned 8-bit integer type.
typedef unsigned char u8;

/// Unsigned 16-bit integer type.
typedef unsigned short u16;

/// Unsigned 32-bit integer type.
typedef unsigned int u32;

/// Unsigned 64-bit integer type.
typedef unsigned long long u64;

/// Signed 8-bit integer type.
typedef signed char i8;

/// Signed 16-bit integer type.
typedef signed short i16;

/// Signed 32-bit integer type.
typedef signed int i32;

/// Signed 64-bit integer type.
typedef signed long long i64;

/// Single-precision floating-point type.
typedef float f32;

/// Double-precision floating-point type.
typedef double f64;

/// Boolean 32-bit type.
typedef int b32;

/// Boolean 8-bit type.
typedef char b8;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

#define TRUE 1
#define FALSE 0
#define true TRUE
#define false FALSE

// Platform detection following defined for each platform -- rewritten from memory

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define CVUL_PLAT_WIN 1
#ifndef _WIN64
#error "Windows must be on 64-bit."
#endif

#elif defined(__linux__) || defined(__gnu_linux__)
#define CVUL_PLAT_LINUX 1
#if defined(__ANDROID__)
#define CVUL_PLAT_ANDROID 1
#endif

#elif defined(__unix__)
#define CVUL_PLAT_UNIX 1

#elif defined(_POSIX_VERSION)
#define CVUL_PLAT_POSIX 1

#elif __APPLE__
#define CVUL_PLAT_APPLE 1
#include <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR
#define CVUL_PLAT_IOS 1
#define CVUL_PLAT_IOS_SIMULATOR 1

#elif TARGET_OS_IPHONE
#define CVUL_PLAT_IOS 1

#elif TARGET_OS_MAC
// TODO add MacOS 
#else
#error "Cannot find type of iOS platform."
#endif
#else
#error "Cannot find platform."
#endif

// DLL Exporting
// When making build files, please add a define flag -DCVULEXPORT
#ifdef CVULEXPORT
#ifdef _MSC_VER
#define CVUL_DLL __declspec(dllexport)
#else
#define CVUL_DLL __attribute__((visibility("default")))
#endif

// DLL Importing
#else
#ifdef _MSC_VER
#define CVUL_DLL __declspec(dllimport)
#else
#define CVUL_DLL
#endif
#endif