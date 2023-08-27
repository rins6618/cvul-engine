#include "game.h"
#include <entry.h>

// NOTE: Testing
#include <platform/platform.h>

b8 create_game(game* out_game)
{
    out_game->app_config.name = "Janeloncio";
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.start_x = 0;
    out_game->app_config.start_y = 0;

    out_game->initialize = game_intitialize;
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->on_resize = game_onresize;

    out_game->state = platform_alloc(sizeof(gamestate), false);
    return true;
}