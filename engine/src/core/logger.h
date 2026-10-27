#pragma once

#include "defines.h"

#define WF_ASSERTIONS_ENABLED

#ifdef COMPILE_DEBUG
#define WF_LOG_LEVEL 5
#else
#define WF_LOG_LEVEL 3
#endif

// LOGGER

enum LogLevel
{
    FATAL = 0,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE
};

b32 logger_init();
void logger_shutdown();

WFAPI void message_log(enum LogLevel log_level, const char *message, ...);

#if WF_LOG_LEVEL >= 0
#define WF_FATAL(message, ...) message_log(FATAL, message, ##__VA_ARGS__);
#else
#define WF_FATAL(message, ...)
#endif

#if WF_LOG_LEVEL >= 1
#define WF_ERROR(message, ...) message_log(ERROR, message, ##__VA_ARGS__);
#else
#define WF_ERROR(message, ...)
#endif

#if WF_LOG_LEVEL >= 2
#define WF_WARN(message, ...) message_log(WARN, message, ##__VA_ARGS__);
#else
#define WF_WARN(message, ...)
#endif

#if WF_LOG_LEVEL >= 3
#define WF_INFO(message, ...) message_log(INFO, message, ##__VA_ARGS__);
#else
#define WF_INFO(message, ...)
#endif

#if WF_LOG_LEVEL >= 4
#define WF_DEBUG(message, ...) message_log(DEBUG, message, ##__VA_ARGS__);
#else
#define WF_DEBUG(message, ...)
#endif

#if WF_LOG_LEVEL >= 5
#define WF_TRACE(message, ...) message_log(TRACE, message, ##__VA_ARGS__);
#else
#define WF_TRACE(message, ...)
#endif

// ASSERTIONS
#ifdef WF_ASSERTIONS_ENABLED

#define WF_ASSERT(expression)                                                                                          \
    {                                                                                                                  \
        if (!(expression))                                                                                             \
        {                                                                                                              \
            WF_FATAL("ASSERTION FAILURE\n\t\tEXPRESSION: %s\n\t\tLINE: %d\n\t\tFILE: %s", #expression, __LINE__,       \
                     __FILE__);                                                                                        \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    }

#define WF_ASSERT_MSG(expression, message)                                                                             \
    {                                                                                                                  \
        if (!(expression))                                                                                             \
        {                                                                                                              \
            WF_FATAL("ASSERTION FAILURE\n\t\tEXPRESSION: %s\n\t\tLINE: %d\n\t\tFILE: %s\n\t\tMESSAGE: %s",             \
                     #expression, __LINE__, __FILE__, message);                                                        \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    }

#ifdef COMPILE_DEBUG
#define WF_ASSERT_DEBUG(expression, message)                                                                           \
    {                                                                                                                  \
        if (!(expression))                                                                                             \
        {                                                                                                              \
            WF_FATAL("ASSERTION FAILURE\n\t\tEXPRESSION: %s\n\t\tLINE: %d\n\t\tFILE: %s\n\t\tMESSAGE: %s",             \
                     #expression, __LINE__, __FILE__, message);                                                        \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    }
#else
#define WF_ASSERT_DEBUG(expression, message) (expression)
#endif
#else
#define WF_ASSERT(expression) (expression)
#define WF_ASSER_MSG(expression) (expression)
#define WF_ASSERT_DEBUG(expression) (expression)
#endif
