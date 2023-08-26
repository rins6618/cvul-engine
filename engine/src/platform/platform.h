#pragma once
#include "def.h"

typedef struct platform_state
{
    void* internal_state;
} platform_state;


// platform starting and shutdown

// Taking the state, app name and window values, initialize the app as a OS process (and subsequently window, if supported) (??)
// Implemented
CVUL_DLL b8 platform_startup(
    platform_state* p_state,
    const char* app_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height);

// Closes the platform process
// Implemented
CVUL_DLL void platform_shutdown(platform_state* p_state);

// Sends out system messages for process - Implemented
// Implemented
CVUL_DLL b8 platform_pump_messages(platform_state* p_state);

// memory

// Allocate memory region - 
void* platform_alloc(u64 size, b8 alligned);
void platform_free(void* block, b8 alligned);
void* platform_zeromem(void* block, u64 size);
void* platform_copymem(void* dest, const void* source, u64 size);
void* platform_setmem(void* dest, i32 val, u64 size);

// console output
CVUL_DLL void platform_console_write(const char* message, u8 color);
CVUL_DLL void platform_console_write_err(const char* message, u8 color);

// time

// Gets absolute time
f64 platform_get_abstime();

// Blocks main thread for specified ms.
// Do not export - should be used for the OS
void platform_sleep(u64 ms);
