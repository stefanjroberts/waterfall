#include "display_wayland.h"
#include <core/logger.h>
#include <string.h>
#include <wayland-client.h>

// CALLBACKS

static void registry_handle_global(void *data, struct wl_registry *registry, u32 name, const char *interface,
                                   u32 version)
{
    struct DisplayServerContext *platform_context = (struct DisplayServerContext *)data;
    if (strcmp(interface, wl_compositor_interface.name) == 0) // TODO: Manual string comparison?
    {
        platform_context->compositor_index = name;
    }
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry, u32 name)
{
    return;
}

// STRUCTURES

static const struct wl_registry_listener registry_listener = {registry_handle_global, registry_handle_global_remove};

// METHODS

void initialize_display_server(struct DisplayServerContext *context)
{
    context->display = wl_display_connect(NULL);

    if (!context->display)
    {
        WF_FATAL("Unable to create wayland display");
        return;
    }

    WF_DEBUG("Wayland display created.");

    // SUBFUNC : Initialise registry and create a surface

    context->registry = wl_display_get_registry(context->display);
    wl_registry_add_listener(context->registry, &registry_listener, (void *)context);
    wl_display_roundtrip(context->display);

    context->compositor = wl_registry_bind(context->registry, context->compositor_index, &wl_compositor_interface, 4);
    if (!context->compositor)
    {
        WF_FATAL("Failed to bind compositor.");
        return;
    }

    WF_DEBUG("Wayland compositor bound.");

    context->surface = wl_compositor_create_surface(context->compositor);

    if (!context->surface)
    {
        WF_FATAL("Failed to create wayland surface");
        return;
    }

    WF_DEBUG("Wayland surface created.");

    return;
}

void shutdown_display_server(struct DisplayServerContext *context)
{
    wl_display_disconnect(context->display);
}
