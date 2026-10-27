#pragma once

#include "defines.h"

// NOTE: This file is a specification for the structure that the engine expects a game to have.
// This structure includes an initialize function and a state pointer for game-specific state.

struct Game
{
    void *state;
    b32 (*init)();
};
