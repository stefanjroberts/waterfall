#pragma once
#include "defines.h"

void *platform_init(const char *application_name, i32 x, i32 y, i32 width, i32 height);
void platform_shutdown(void *context);

b32 platform_process_messages(void *context);

void *platform_alloc(u64 size, b32 aligned);
void platform_free(void *memoryptr, b32 aligned);
void platform_clear_memory(void *memoryptr, u64 size);
void platform_copy_memory(void *dest, void *source, u64 size);
void platform_set_memory(void *memoryptr, i32 value, u64 size);

void platform_console_print(char *message, i32 colour);

u64 platform_get_time();
void platform_sleep(u64 microseconds);
