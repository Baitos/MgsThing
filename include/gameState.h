#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "state.h"
#include "object.h"
#include "player.h"

// for future reference, make sure to not put raw points, file handlers, or non-copyables
// we need to be able to restore previous gameStates for rollback to work

struct GameState {    
    SDL_FRect mapViewport;
    bool debugMode;

    Player player;
    std::vector<Object> mapTiles;
    std::vector<Object> fgTiles;
    

    
    GameState(const SDLState &state, Resources &res) 
        : mapViewport {
            0.0f, 
            0.0f,
            (float)state.logW,
            (float)state.logH
        },
        debugMode(false),
        player(glm::vec2(0.f), 4)
    {
        init(state, res);
    }
    GameState() = default;
    void init(const SDLState &state, Resources &res);
    void loadMap(const SDLState& state, Resources& res, const std::string& path);
};