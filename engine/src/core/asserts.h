// note to self: the file is named asserts due to the prebuilt headers already named assert
#pragma once
#include "def.h"

#define CVUL_ENABLE_ASSERTS 1

#ifdef CVUL_ENABLE_ASSERTS
#if _MSC_VER
#include <intrin.h>
#define break_exec() __debugbreak()
#else
#define break_exec() __builtin_trap()
#endif

// the linker thinks this is fake. why? 
CVUL_DLL void report_false_assert(const char* exp, const char* message, const char* filepath, i32 line);

#define CVUL_ASSERT(expression)                                 \
{                                                               \
    if (expression)                                             \
    {}                                                          \
    else                                                        \
    {                                                           \
    report_false_assert(#expression, "", __FILE__, __LINE__);   \
    break_exec();                                               \
    }                                                           \
}

#define CVUL_ASSERTMSG(expression, msg)\
{\
    if (expression)\
    {}\
    else\
    {\
    report_false_assert(#expression, msg, __FILE__, __LINE__);\
    break_exec();\
    }\
}

#ifdef _DEBUG
#define CVUL_ASSERTDEBUG(expression)\
{\
    if (expression)\
    {}\
    else\
    {\
        report_false_assert(#expression, msg, __FILE__, __LINE__);\
        break_exec();\
    }\
}

#else
#define CVUL_ASSERTDEBUG(expression)  // Does nothing at all
#endif

#else
#define CVUL_ASSERT(expression)
#define CVUL_ASSERTMSG(expression, msg)
#define CVUL_ASSERTDEBUG(expression)
#endif