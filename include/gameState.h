#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "state.h"
#include "object.h"
#include "player.h"

struct GameState {    
    SDL_FRect mapViewport;
    bool debugMode;

    Player player;
    std::vector<Object> mapTiles_;
    std::vector<Object> fgTiles_;

    GameState(const SDLState &state) {
        mapViewport = SDL_FRect {
            .x = 0,
            .y = 0,
            .w = static_cast<float>(state.logW),
            .h = static_cast<float>(state.logH)
        };
        debugMode = false;
    }
};