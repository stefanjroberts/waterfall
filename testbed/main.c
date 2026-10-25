#include <core/core_module.h>
#include <platform/platform_module.h>

int main(void)
{
    WF_FATAL("fatal");
    WF_ERROR("fatal");
    WF_WARN("fatal");
    WF_INFO("fatal");
    WF_DEBUG("fatal");
    WF_TRACE("fatal");

    void *platform_context = platform_init("Test Window", 0, 0, 600, 800);

    platform_shutdown(platform_context);

    return 0;
}
