#include "renderer_frontend.h"
#include "core/wfmemory.h"
#include "renderer_backend.h"

struct RendererFrontendContext
{
    void *renderer_backend;
};

void *renderer_frontend_init()
{
    struct RendererFrontendContext *renderer_frontend_context =
        wf_allocate(sizeof(struct RendererFrontendContext), MEMTAG_RENDERER);

    renderer_frontend_context->renderer_backend = renderer_backend_init();

    return (void *)renderer_frontend_context;
}
