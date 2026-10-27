#pragma once
#include "defines.h"

struct DisplayServerContext
{
    struct wl_display *display;
    struct wl_registry *registry;
    u32 compositor_index;
    struct wl_compositor *compositor;
    struct wl_surface *surface;
};

void initialize_display_server(struct DisplayServerContext *context);
void shutdown_display_server(struct DisplayServerContext *context);
