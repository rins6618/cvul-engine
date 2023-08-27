#pragma once

#include "core/logging.h"
#include "core/application.h"
#include "game_type.h"

extern b8 create_game(game* out_game);

int main(void)
{

    game game_instance;
    if (!create_game(&game_instance))
    {
        CVUL_FATAL("Game could not be created!");
        return -1;
    }

    if (!game_instance.initialize || !game_instance.update || 
    !game_instance.render || !game_instance.on_resize)
    {
        CVUL_FATAL("All the function pointers must be defined!");
        return -2;
    }

    if (!app_start(&game_instance))
    {
        CVUL_INFO("Application failed to create!");
        return 1;
    }

    if (!app_run())
    {
        CVUL_INFO("Application did not shutdown correctly!");
        return 2;
    }
}