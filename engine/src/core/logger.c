#include "logger.h"
#include <platform/platform_module.h>
#include <stdarg.h> //Necessary to use variadic arguments
#include <stdio.h>  // Necessary for printing //libraries

b32 initalize_logging()
{
    // TODO: Create a log output file to write to.
    return TRUE;
}

void shutdown_logging()
{
    // TODO: Flush buffer and write to output file.
    return;
}

void log_message(enum LogLevel log_level, const char *message, ...)
{
    const i32 level_name_length = 9;
    const char *level_names[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    char formatted_message[16000] = {0}; // NOTE: 16k character limit on log message.

    sprintf(formatted_message, "%s", level_names[log_level]);
    va_list argument_ptr;
    va_start(argument_ptr, message);
    vsnprintf(formatted_message + level_name_length, 16000 - level_name_length, message, argument_ptr);
    va_end(argument_ptr);

    platform_console_print(formatted_message, (i32)log_level); // NOTE:Explicit cast necessary for C++ compatibility
    return;
}
