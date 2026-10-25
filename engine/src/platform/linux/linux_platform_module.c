#include <defines.h>
#if WF_PLATFORM_LINUX
#include "platform/platform_module.h"
#include <stdio.h>

void platform_print_message(char *message, i32 colour)
{
    const char *colour_codes[6] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m \n", colour_codes[colour], message);
    return;
}

#endif
