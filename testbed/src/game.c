#include "game.h"

#include <core/logging.h>

b8 game_intitialize(game* game_instance)
{
    CVUL_DEBUG("game_initialize() function called!");
    return true;
}

b8 game_update(game* game_instance, f32 delta_time)
{
    return true;
}

b8 game_render(game* game_instance, f32 delta_time)
{
    return true;
}

void game_onresize(game* game_instance, u32 width, u32 height)
{
}