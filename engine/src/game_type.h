#pragma once
#include "core/application.h"

// A structure representing a game.
typedef struct game {
    /// Configuration for the game's application.
    app_config app_config;

    /// Pointer to the initialization function for the game.
    /// @param game_inst A pointer to the game instance.
    /// @return TRUE if initialization was successful, otherwise FALSE.
    b8 (*initialize) (struct game* game_inst);

    /// Pointer to the update function for the game.
    /// @param game_inst A pointer to the game instance.
    /// @param delta_time The time elapsed since the last game update.
    /// @return TRUE if the update was successful, otherwise FALSE.
    b8 (*update) (struct game* game_inst, f32 delta_time);

    /// Pointer to the render function for the game.
    /// @param game_inst A pointer to the game instance.
    /// @param delta_time The time elapsed since the last frame rendered.
    /// @return TRUE if rendering was successful, otherwise FALSE.
    b8 (*render) (struct game* game_inst, f32 delta_time);

    /// Pointer to the on_resize function for the game.
    void (*on_resize) (struct game* game_inst, u32 width, u32 height);

    /// A pointer to the game's state.
    void* state;
} game;

