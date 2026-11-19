#include "core/logger.h"
#include "core/wfmemory.h"
#include "vulkan_backend.h"

VkBool32 debug_message_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                VkDebugUtilsMessageTypeFlagsEXT message_type,
                                const VkDebugUtilsMessengerCallbackDataEXT *callback_data, void *user_data)
{
    if (message_severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
    {
        WF_ERROR("VULKAN DEBUG LAYER\n%s", callback_data->pMessage);
    }
    if (message_severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        WF_WARN("VULKAN DEBUG LAYER\n%s", callback_data->pMessage);
    }
    if (message_severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
    {
        WF_INFO("VULKAN DEBUG LAYER\n%s", callback_data->pMessage);
    }
    return VK_FALSE;
}

VkInstance vulkan_instance_create()
{
    VkInstance instance = 0;
    VkApplicationInfo application_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    VkInstanceCreateInfo instance_create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    VkResult create_instance_result;

    application_info.pApplicationName = "Waterfall Engine";
    application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.pEngineName = "Waterfall";
    application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.apiVersion = VK_MAKE_API_VERSION(0, 1, 4, 0);

    instance_create_info.pApplicationInfo = &application_info;
    instance_create_info.enabledLayerCount = requested_layer_count;
    instance_create_info.ppEnabledLayerNames = requested_layers;
    instance_create_info.enabledExtensionCount = requested_extension_count;
    instance_create_info.ppEnabledExtensionNames = requested_extensions;

    // TODO: Implement checking for layer/extension presence

    create_instance_result = vkCreateInstance(&instance_create_info, NULL, &instance);

    if (create_instance_result != VK_SUCCESS)
    {
        WF_ERROR("Failed to create vulkan instance\n\tError: %d", create_instance_result);
        return 0;
    }

    return instance;
}

VkDebugUtilsMessengerEXT vulkan_debug_messenger_create(struct VulkanContext *context)
{
    VkDebugUtilsMessengerEXT debug_messenger = 0;
    VkDebugUtilsMessengerCreateInfoEXT debug_messenger_create_info = {
        VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
    PFN_vkCreateDebugUtilsMessengerEXT debug_messenger_create_function = 0;
    VkResult debug_messenger_create_result;

    debug_messenger_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
    debug_messenger_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                              VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_messenger_create_info.pfnUserCallback = debug_message_callback;

    debug_messenger_create_function =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context->instance, "vkCreateDebugUtilsMessengerEXT");

    if (debug_messenger_create_function == 0)
    {
        WF_ERROR("Unable to find debug messenger creation function");
        return 0;
    }

    debug_messenger_create_result =
        debug_messenger_create_function(context->instance, &debug_messenger_create_info, NULL, &debug_messenger);

    if (debug_messenger_create_result != VK_SUCCESS)
    {
        WF_ERROR("Failed to create vulkan debug messenger\n\tError: %d", debug_messenger_create_result);
        return 0;
    }

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

    context->debug_messenger = vulkan_debug_messenger_create(context);

    if (context->debug_messenger == 0)
    {
        WF_ERROR("Renderer initialisation failed.");
        return 0;
    }

    return (void *)context;
}
