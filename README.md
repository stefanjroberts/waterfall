# PROJECT OUTLINE

Intent: Make a game engine built around data oriented design. Make profiling tools and an editor that facilitates this workflow.

Components: Two primitive types, components (data) and jobs (functions) with jobs acting on components. Components can be assembled into entities, and jobs can act on a subset of entities defined by user.

Jobs will be managed by the job system, which will organise parallel execution using signals (semaphores). No scripting is required, all functionality is implemented via the job system. (That is, scripts are executed as jobs).

In essence: everything is a job.

Profiling tools:
1. A display which shows a breakdown of a frame, showing all jobs and semaphores at varying levels of granularity.
2. A display which shows concurrent jobs across frames (i.e. jobs for frame 2 instantiated before frame 1 is displayed)
3. A display which shows cache utilisation and places where Job transitions result in cache misses. General information about the cache state.

Editor:
1. Starting data construction (placing models, loading assets, initialising data structures, etc.)
2. Job graph (creating scripts, creating jobs, creating semaphores, etc.)
