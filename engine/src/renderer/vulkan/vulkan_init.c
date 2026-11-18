#include "core/logger.h"
#include "core/wfmemory.h"
#include "vulkan_backend.h"

VkInstance vulkan_instance_create()
{
    VkInstance instance = 0;

    VkApplicationInfo application_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    application_info.pApplicationName = "Waterfall Engine";
    application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.pEngineName = "Waterfall";
    application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.apiVersion = VK_MAKE_API_VERSION(0, 1, 4, 0);

    VkInstanceCreateInfo instance_create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    instance_create_info.pApplicationInfo = &application_info;
    instance_create_info.enabledLayerCount = requested_layer_count;
    instance_create_info.ppEnabledLayerNames = requested_layers;
    instance_create_info.enabledExtensionCount = requested_extension_count;
    instance_create_info.ppEnabledExtensionNames = requested_extensions;

    // TODO: Implement checking for layer/extension presence

    VkResult result = vkCreateInstance(&instance_create_info, NULL, &instance);

    if (result != VK_SUCCESS)
    {
        WF_ERROR("Failed to create vulkan instance\n\tError: %d", result);
        return 0;
    }

    return instance;
}

VkDebugUtilsMessengerEXT vulkan_debug_messenger_create()
{
    VkDebugUtilsMessengerEXT debug_messenger = 0;

    return debug_messenger;
}

void *renderer_backend_init()
{
    struct VulkanContext *context = wf_allocate(sizeof(struct VulkanContext), MEMTAG_RENDERER);

    context->instance = vulkan_instance_create();

    if (context->instance == 0)
    {
        WF_ERROR("Renderer initialisation failed.");
        return 0;
    }

    context->debug_messenger = vulkan_debug_messenger_create();

    return (void *)context;
}
