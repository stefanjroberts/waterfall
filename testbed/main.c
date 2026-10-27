#include "core/logger.h"
#include "core/wfmemory.h"
#include "modules/engine_runtime.h"
int main(void)
{
    struct EngineInitInfo init_info = {"Test Application", 0, 0, 600, 800};

    if (!engine_init(init_info))
    {
        WF_FATAL("Engine initalisation failed, shutting down...");
        return 1;
    }

    void *allocation = wf_allocate(1024 * 100, MEMTAG_DEFAULT);

    memory_allocations_print();

    wf_free(allocation, 1024 * 100, MEMTAG_DEFAULT);

    memory_allocations_print();

    engine_run();

    WF_INFO("Shutting down...");

    return 0;
}
