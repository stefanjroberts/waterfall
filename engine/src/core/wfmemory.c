#include "wfmemory.h"
#include "core/logger.h"
#include "modules/platform.h"
#include <stdio.h>

// TODO: This file contains static globals, but since this is being included directly in core.c they are more visible
// than they probably should be, consider isolating this file in particular
// TODO: Additionally, figure out how each individual module should manage its memory, should it be assigned a single
// memory block, or should this allocator just assign memory within each block and manage those itself?

struct MemoryInfo
{
    u64 allocated;
    u64 allocated_by_tag[MEMTAG_MAX];
};

static const char *tag_names[MEMTAG_MAX] = {
    "MEMTAG_DEFAULT", "MEMTAG_STARTUP", "MEMTAG_LOGGER", "MEMTAG_RENDERER", "MEMTAG_JOB",
    "MEMTAG_ECS",     "MEMTAG_AUDIO",   "MEMTAG_TEMP",   "MEMTAG_TEST",
};

static struct MemoryInfo _memory_info = {0};

void memory_allocations_print()
{
    char allocation_table[8000] = {0};
    const char *prefix_table[4] = {"B", "KiB", "MiB", "GiB"}; // Can't allocate terabytes
    f32 prefix_sizes[4] = {1, 1024, 1024 * 1024, 1024 * 1024 * 1024};
    i32 offset = 0;

    // SUBFUNC: Print out total memory usage;
    u32 prefix_power = 0;
    for (i32 j = 0; j < 4; j++)
    {
        if ((_memory_info.allocated >> (8 * j)) <= 1024)
        {
            prefix_power = j;
            break;
        }
    }

    f32 allocation_size = ((float)_memory_info.allocated) / prefix_sizes[prefix_power];

    offset = snprintf(allocation_table, 8000, "MEMORY ALLOCATIONS:\n\tTOTAL: %.2f%s\n", allocation_size,
                      prefix_table[prefix_power]);

    // SUBFUNC: Print out each memory tag allocation

    for (i32 i = 0; i < MEMTAG_MAX; i++)
    {
        for (i32 j = 0; j < 4; j++)
        {
            if ((_memory_info.allocated_by_tag[i] >> (8 * j)) <= 1024)
            {
                prefix_power = j;
                break;
            }
        }
        allocation_size = ((float)_memory_info.allocated_by_tag[i]) / prefix_sizes[prefix_power];

        offset += snprintf(allocation_table + offset, 8000 - offset, "\t\t%s: %.2f%s\n", tag_names[i], allocation_size,
                           prefix_table[prefix_power]);
    }

    WF_INFO("%s", allocation_table);
}

void wf_zero_memory(void *memoryptr, u64 size)
{
    platform_zero_memory(memoryptr, size);
}
void wf_copy_memory(void *dest, void *src, u64 size)
{
    platform_copy_memory(dest, src, size);
}
void wf_set_memory(void *memoryptr, i32 value, u64 size)
{
    platform_set_memory(memoryptr, value, size);
}

#if (MEMORY_DEBUG_ENABLED == 0)
void *wf_allocate(u64 size, enum MemoryTag memtag)
{
    if (memtag == MEMTAG_DEFAULT)
    {
        WF_WARN("Memory allocated with MEMTAG_DEFAULT");
    }
    if (memtag == MEMTAG_TEST)
    {
        WF_INFO("Memory allocated with MEMTAG_TEST: %d Bytes", size);
    }
    _memory_info.allocated += size;
    _memory_info.allocated_by_tag[memtag] += size;
    return platform_alloc(size, FALSE);
}

void wf_free(void *memoryptr, u64 size, enum MemoryTag memtag)
{
    if (memtag == MEMTAG_DEFAULT)
    {
        WF_WARN("Memory freed with MEMTAG_DEFAULT");
    }
    if (memtag == MEMTAG_TEST)
    {
        WF_INFO("Memory deallocated with MEMTAG_TEST: %d Bytes", size);
    }
    _memory_info.allocated -= size;
    _memory_info.allocated_by_tag[memtag] -= size;
    platform_free(memoryptr, FALSE);
}

#else
// NOTE: Debug memory allocator
void *_debug_wf_allocate(u64 size, enum MemoryTag memtag, u64 line, const char *file)
{
    char *memoryptr = (char *)platform_alloc(size + 40, FALSE);
    memoryptr += 32; // NOTE: Header is 32 bytes long
    u64 *header = (u64 *)memoryptr;
    header[-1] = size;                                    // NOTE: Record size of allocation
    header[-2] = (u64)file;                               // NOTE: Record file that did allocation
    header[-3] = line;                                    // NOTE: Record line that did allocation
    platform_set_memory(header - 4, 0xCDCDCDCD, 8);       // NOTE: Check for overwriting below buffer
    platform_set_memory(memoryptr + size, 0xCDCDCDCD, 8); // NOTE: Check for overwriting above buffer
    return memoryptr;
}

void _debug_wf_free(void *memoryptr, u64 size, enum MemoryTag memtag, u64 line, const char *file)
{
    u64 *header = (u64 *)memoryptr;
    if ((header[-4] != 0xCDCDCDCDCDCDCDCD) || (header[size] != 0xCDCDCDCDCDCDCDCD))
    {
        WF_ERROR("DATA CORRUPTION DETECTED, DEALLOCATION IN \n\t\tFILE: %s \n\t\tLINE: %d", file, line);
    }
    if (header[-1] != size)
    {
        WF_ERROR("Tried to deallocate memory block of wrong size\n ALLOCATED SIZE: %d\n DEALLOC SIZE: %d\n ALLOCATED "
                 "IN FILE: %s, LINE: %d\n DEALLOCATED IN FILE: %s, LINE: %d",
                 header[-1], size, (const char *)header[-2], header[-3], file, line);
    }
}

void validate_memory(u64 line, const char *file)
{
    // TODO: Implement a memory validator that checks for buffer overruns and other bad states
}
#endif
