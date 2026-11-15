#pragma once

// Custom integer and float types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

typedef int b32;

// Check that the types are the correct size
_Static_assert(sizeof(u8) == 1, "u8 wrong size");
_Static_assert(sizeof(u16) == 2, "u16 wrong size");
_Static_assert(sizeof(u32) == 4, "u32 wrong size");
_Static_assert(sizeof(u64) == 8, "u64 wrong size");

_Static_assert(sizeof(i8) == 1, "u8 wrong size");
_Static_assert(sizeof(i16) == 2, "i16 wrong size");
_Static_assert(sizeof(i32) == 4, "i32 wrong size");
_Static_assert(sizeof(i64) == 8, "i64 wrong size");

_Static_assert(sizeof(f32) == 4, "f32 wrong size");
_Static_assert(sizeof(f64) == 8, "f64 wrong size");

#define TRUE 1
#define FALSE 0

// Platform detection
#if defined(__linux__) || defined(__gnu_linux__)
#define WF_PLATFORM_LINUX 1
#endif

// Check if building for library or API.
#ifdef WF_EXPORT
#define WFAPI __attribute__((visibility("default")))
#else
#define WFAPI
#endif

// NOTE: Only vulkan renderer currently supported
#define VULKAN_BACKEND 1
