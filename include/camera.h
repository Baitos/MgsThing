#pragma once

#include <SDL3/SDL.h>
#include "state.h"
#include <vector>

class Object;

class Camera {
    public:
        float x; // x pos
        float y; // y pos
        float w; // width
        float h; // height
        Camera(const SDLState &state) {
            x = y = 0.0f;
            w = static_cast<float>(state.logW);
            h = static_cast<float>(state.logH);
        }
        Camera() {
            x = y = w = h = 0.0f;
        }
        void renderOnscreenTiles(const SDLState& state, GameState& gs, Resources& res, std::vector<Object>& tileLayer, int mapWidth, int mapHeight);
};