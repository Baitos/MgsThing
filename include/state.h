#pragma once

#include <stdint.h>
#include "input.h"

struct SDL_Window;
struct SDL_Renderer;

struct FrameState // anything related to deltaTime and fps
{
    uint64_t prevTime; 
    uint64_t frames;
    uint64_t FPS;
    uint64_t lastTime;
    float deltaTime;
    uint64_t nowTime;
    FrameState() {
        prevTime = 0;
        frames = 0;
        FPS = 0;
        lastTime = 0;
        float deltaTime = 0;
    }
};

struct SDLState
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width, height, logW, logH;
    float xRatio, yRatio;

    const bool *keys;

    FrameState fs;
    InputManager im;

    SDLState() : keys(SDL_GetKeyboardState(nullptr)) {
    }
};

bool initialize(SDLState &state);
void cleanup(SDLState &state);

void advanceTime(SDLState &state); // run deltaTime logic