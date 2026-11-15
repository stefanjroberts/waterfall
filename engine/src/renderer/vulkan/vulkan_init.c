#include "core/wfmemory.h"
#include "vulkan_backend.h"

VkInstance vulkan_create_instance()
{
    VkInstance instance;

    // TODO: INSTANCE CREATION

    return instance;
}

void *renderer_backend_init()
{
    struct VulkanContext *context = wf_allocate(sizeof(struct VulkanContext), MEMTAG_RENDERER);

    context->instance = vulkan_create_instance();

    return (void *)context;
}
