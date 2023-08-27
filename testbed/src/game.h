#pragma once

#include <def.h>
#include <game_type.h>

typedef struct gamestate {
    f32 delta_time;
} gamestate;

b8 game_intitialize(game* game_instance);
b8 game_update(game* game_instance, f32 delta_time);
b8 game_render(game* game_instance, f32 delta_time);
void game_onresize(game* game_instance, u32 width, u32 height);