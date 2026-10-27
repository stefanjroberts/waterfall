#include <defines.h>
#if WF_PLATFORM_LINUX
#include "modules/platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "platform/linux/display_wayland.c"
// TODO: Implement Xorg version

struct LinuxPlatformContext
{
    struct timespec start_time;
    struct DisplayServerContext display_server;
};

void *platform_init(const char *application_name, i32 x, i32 y, i32 width, i32 height)
{
    struct LinuxPlatformContext *context = (struct LinuxPlatformContext *)malloc(sizeof(struct LinuxPlatformContext));

    clock_gettime(CLOCK_MONOTONIC, &context->start_time);

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
void platform_zero_memory(void *memoryptr, u64 size)
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

u64 platform_get_time()
{
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    return current_time.tv_sec * 1000 * 1000 * 1000 +
           current_time.tv_nsec; // NOTE: MAX_UINT64 nanoseconds is ~580 years
}
void platform_sleep(u64 microseconds)
{
    struct timespec sleep_time;
    sleep_time.tv_nsec = (microseconds % (1000000)) * 1000;
    sleep_time.tv_sec = microseconds / (1000 * 1000);
}

#endif
