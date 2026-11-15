#pragma once

#if (VULKAN_BACKEND == 1)
#include "renderer_backend.h"
#endif

void *renderer_frontend_init();
void renderer_frontend_destroy();
