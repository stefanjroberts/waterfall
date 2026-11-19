#pragma once
#include <vulkan/vulkan.h>

struct VulkanContext
{
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
};

// TODO: Remove hardcoded renderer parameters.
// Handling other platforms also relies on removing hardcoding of wayland surface extension.

const int requested_layer_count = 1;
const char *const requested_layers[] = {"VK_LAYER_KHRONOS_validation"};
const int requested_extension_count = 4;
const char *const requested_extensions[] = {"VK_KHR_swapchain", "VK_KHR_surface", "VK_KHR_wayland_surface",
                                            "VK_EXT_debug_uitls"};
