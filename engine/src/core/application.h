#pragma once
#include "def.h"
struct game;

/// @brief Configuration for the app to be initialized
typedef struct app_config
{
    /// @brief A string representing the name of the app, if applicable
    char* name;
    /// @brief An int representing the start X position of the app's window, if applicable
    i32 start_x;
    /// @brief An int representing the start Y position of the app's window, if applicable
    i32 start_y;
    /// @brief An int representing the starting width the app's window, if applicable
    i32 start_width;
    /// @brief An int representing the starting height of the app's window, if applicable
    i32 start_height;

} app_config;

CVUL_DLL b8 app_start(struct game* game_instance);

CVUL_DLL b8 app_run();