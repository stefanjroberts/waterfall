#pragma once

#include "defines.h"

// NOTE: Set DEBUG_MEMORY to 1 to perform more meticulous memory debugging (slow). Set to 0 to use standard memory
// management.
#define MEMORY_DEBUG_ENABLED 0

enum MemoryTag
{
    MEMTAG_DEFAULT,
    MEMTAG_STARTUP,
    MEMTAG_LOGGER,
    MEMTAG_RENDERER,
    MEMTAG_JOB,
    MEMTAG_ECS,
    MEMTAG_AUDIO,
    MEMTAG_TEMP,
    MEMTAG_TEST,

    MEMTAG_MAX
};

void memory_init();
void memory_shutdown();

WFAPI void memory_allocations_print();

WFAPI void wf_zero_memory(void *memoryptr, u64 size);
WFAPI void wf_copy_memory(void *dest, void *src, u64 size);
WFAPI void wf_set_memory(void *memoryptr, i32 value, u64 size);

// NOTE: preprocessor replaces memory management functions with debug versions that record additional info.
#if (MEMORY_DEBUG_ENABLED == 0)
#define VALIDATE_MEMORY()
WFAPI void *wf_allocate(u64 size, enum MemoryTag memtag);
WFAPI void wf_free(void *memoryptr, u64 size, enum MemoryTag memtag);
#else
#define VALIDATE_MEMORY() validate_memory(__LINE__, __FILE__);
#define wf_allocate(size, memtag) _debug_wf_allocate(size, memtag, __LINE__, __FILE__);
#define wf_free(memoryptr, size, memtag) _debug_wf_free(memoryptr, size, memtag, __LINE__, __FILE__);
WFAPI void validate_memory(u64 line, const char *file);
WFAPI void *_debug_wf_allocate(u64 size, enum MemoryTag memtag, u64 line, const char *file);
WFAPI void _debugwf_free(void *memoryptr, u64 size, enum MemoryTag memtag, u64 line, const char *file);
#endif
