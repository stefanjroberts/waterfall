#include <core/core_module.h>
#include <platform/platform_module.h>

int main(void)
{

    void *platform_context = platform_init("Test Window", 0, 0, 600, 800);
    if (platform_context == 0)
    {
        WF_FATAL("Failed to initalise platform layer.");
        return 1;
    }

    platform_shutdown(platform_context);

    return 0;
}
