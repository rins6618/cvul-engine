#pragma once
#include "def.h"

#define LOG_ENABLE_WARNS 1
#define LOG_ENABLE_INFO  1
#define LOG_ENABLE_DEBUG 1
#define LOG_ENABLE_TRACE 1

#if CVUL_RELEASE_BUILD == 1
#define LOG_ENABLE_DEBUG 0
#define LOG_ENABLE_TRACE 0
#endif

typedef enum log_level {
    LOG_FATAL = 0, LOG_ERROR = 1, LOG_WARN = 2,
    LOG_INFO = 3, LOG_DEBUG = 4, LOG_TRACE = 5
} log_level;

b8 init_log();
void finish_log();

/*Logs to console with message levels - 0 to 6:

Fatal - Error - Warn - Info - Debug - Trace
*/ 
CVUL_DLL void log_console(log_level level, const char* message, ...);

// Logs a fatal error message.
#define CVUL_FATAL(message, ...) log_console(LOG_FATAL, message, ##__VA_ARGS__);

#ifndef CVUL_ERROR
// Logs an error message.
#define CVUL_ERROR(message, ...) log_console(LOG_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_ENABLE_WARNS == 1
// Logs a warning-level message.
#define CVUL_WARN(message, ...) log_console(LOG_WARN, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_WARN_ENABLED != 1
#define CVUL_WARN(message, ...)
#endif

#if LOG_ENABLE_INFO == 1
// Logs a info-level message.
#define CVUL_INFO(message, ...) log_console(LOG_INFO, message, ##__VA_ARGS__);
#else
#define CVUL_INFO(message, ...)
#endif

#if LOG_ENABLE_DEBUG == 1
// Logs a debug-level message.
#define CVUL_DEBUG(message, ...) log_console(LOG_DEBUG, message, ##__VA_ARGS__);
#else
#define CVUL_DEBUG(message, ...)
#endif

#if LOG_ENABLE_TRACE == 1
// Logs a trace-level message.
#define CVUL_TRACE(message, ...) log_console(LOG_TRACE, message, ##__VA_ARGS__);
#else
#define CVUL_TRACE(message, ...)
#endif