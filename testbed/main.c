#include "core/logger.h"
#include "modules/engine_runtime.h"

int main(void)
{
    struct EngineInitInfo init_info = {"Test Application", 0, 0, 600, 800};

    if (!engine_init(init_info))
    {
        WF_FATAL("Engine initalisation failed, shutting down...");
        return 1;
    }

    engine_run();

    WF_INFO("Shutting down...");

    return 0;
}
