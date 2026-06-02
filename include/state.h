#pragma once

#include <stdint.h>
#include "input.h"

struct SDL_Window;
struct SDL_Renderer;

struct FrameState // anything related to deltaTime and fps
{
    uint64_t prevTime = 0; 
    uint64_t frames = 0;
    uint64_t FPS = 0;
    uint64_t lastTime = 0;
    uint64_t nowTime = 0;
    float deltaTime = 0.0f;
};

struct SDLState
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = 1600;
    int height = 900;
    int logW = 800;
    int logH = 450;
    float xRatio = (float)logW / width; 
    float yRatio = (float)logH / height;

    const bool *keys;

    FrameState fs;
    InputManager im;

    SDLState() : keys(SDL_GetKeyboardState(nullptr)) {
    }
};

bool initialize(SDLState &state);
void cleanup(SDLState &state);

void advanceTime(SDLState &state); // run tick logic