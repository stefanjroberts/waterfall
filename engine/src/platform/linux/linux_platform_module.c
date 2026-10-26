#include <defines.h>
#if WF_PLATFORM_LINUX
#include "platform/platform_module.h"
#include <core/logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display_wayland.c"
// TODO: Implement Xorg version

struct LinuxPlatformContext
{
    struct DisplayServerContext display_server;
};

void *platform_init(const char *application_name, i32 x, i32 y, i32 width, i32 height)
{
    struct LinuxPlatformContext *context = (struct LinuxPlatformContext *)malloc(sizeof(struct LinuxPlatformContext));

    initialize_display_server(&(context->display_server));

    return (void *)context;
}

void platform_shutdown(void *platform_context)
{
    struct LinuxPlatformContext *context = (struct LinuxPlatformContext *)platform_context;

    shutdown_display_server(&(context->display_server));

    free(platform_context);

    return;
}

b32 platform_process_messages(void *context)
{
    // TODO: Implement event processing for wayland
    return TRUE;
}

void *platform_alloc(u64 size, b32 aligned)
{
    return malloc(size);
}
void platform_free(void *memoryptr, b32 aligned)
{
    free(memoryptr);
    return;
}
void platform_clear_memory(void *memoryptr, u64 size)
{
    memset(memoryptr, 0, size);
    return;
}
void platform_copy_memory(void *dest, void *src, u64 size)
{
    memcpy(dest, src, size);
    return;
}
void platform_set_memory(void *memoryptr, i32 value, u64 size)
{
    memset(memoryptr, value, size);
}

void platform_console_print(char *message, i32 colour)
{
    const char *colour_codes[6] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m \n", colour_codes[colour], message);
    return;
}

f64 platform_get_time();
void platform_sleep(u64 ms);

#endif
