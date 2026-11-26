#include "engine_runtime.h"
#include "core/logger.h"
#include "defines.h"
#include "platform.h"
#include "renderer/renderer_frontend.h"

// NOTE: This module contains the global runtime information for the entire engine.

struct EngineRuntime
{
    // Application State
    b32 running;
    b32 suspended;

    // Subsystem Contexts
    void *platform_context;
    void *renderer_context;
};

static b32 initialized = FALSE; // NOTE: Keeps track of whether the engine has been initialised more than once
static struct EngineRuntime engine_state;

b32 engine_init(struct EngineInitInfo init_info)
{
    if (initialized)
    {
        WF_ERROR("Engine has been initialised more than once.");
        return FALSE;
    }

    logger_init();

    engine_state.platform_context = platform_init(init_info.application_name, init_info.offset_x, init_info.offset_y,
                                                  init_info.width, init_info.height);
    if (!engine_state.platform_context)
    {
        return FALSE;
    }

    engine_state.renderer_context = renderer_frontend_init();
    if (!engine_state.renderer_context)
    {
        return FALSE;
    }

    return TRUE;
}

b32 engine_run()
{
    while (engine_state.running)
    {
    }
    platform_shutdown(engine_state.platform_context);
    logger_shutdown();
    return TRUE;
}
