#include "application.h"
#include "game_type.h"

#include "logging.h"
#include "platform/platform.h"

typedef struct app_state {
    game* game_inst;
    i16 width;
    i16 height;
    platform_state platform;
    f64 last_time;
    b8 running;
    b8 suspended;
} app_state;


static b8 is_initialized = FALSE;
static app_state state;


b8 app_start(game* game_instance)
{
    if (is_initialized == TRUE)
    {
        // If the app already exists, logging subsystem already is initialized
        
        CVUL_ERROR("Tried to open application %s while it was already open!", game_instance->app_config.name);
        return FALSE;
    }
    state.game_inst = game_instance;

    // Start initializing the subsystems of the engine
    //initialize_logging();


    state.running = TRUE;
    state.suspended = FALSE;


    b8 success = platform_startup(&state.platform, game_instance->app_config.name,
                            game_instance->app_config.start_x, game_instance->app_config.start_y,
                            game_instance->app_config.start_width, game_instance->app_config.start_height);
    if(!success)
    {
        return FALSE;
    }

    if (!state.game_inst->initialize(state.game_inst))
    {
        CVUL_FATAL("Could not initialize game.");
        return FALSE;
    }

    state.game_inst->on_resize(state.game_inst, state.width, state.height);

    is_initialized = TRUE;
    return TRUE;

}

b8 app_run()
{
    while (state.running)
    {
        if (!platform_pump_messages(&state.platform))
        {
            state.running = FALSE;
        }

        if (!state.suspended)
        {
            if (!state.game_inst->update(state.game_inst, (f32)0))
            {
                CVUL_FATAL("Game update function failed - shutting down program");
                state.running = FALSE;
                break;
            }

            if (!state.game_inst->render(state.game_inst, (f32)0))
            {
                CVUL_FATAL("Game render function failed - shutting down program");
                state.running = FALSE;
                break;
            }
        }
    }

    // failsafe
    state.running = FALSE;

    platform_shutdown(&state.platform);

    return TRUE;
}