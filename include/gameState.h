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
    void init(const SDLState &state, Resources &res);
    void loadMap(const SDLState& state, Resources& res, const std::string& path);
};