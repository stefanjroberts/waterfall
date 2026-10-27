#pragma once

#include "defines.h"

struct EngineInitInfo
{
    const char *application_name;
    i32 offset_x;
    i32 offset_y;
    i32 width;
    i32 height;
};

WFAPI b32 engine_init(struct EngineInitInfo);
WFAPI b32 engine_run();
