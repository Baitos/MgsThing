#include <SDL3/SDL.h>
#include <stdio.h>

#include "../include/state.h"
#include "../include/globals.h"
#include "../include/gameState.h"

#include <iostream>

bool initialize(SDLState &state) {
    bool initSuccess = true;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error Initializing SDL3", nullptr);
        printf("Error Initializing SDL3\n");
        initSuccess = false;
    } 
    state.window = SDL_CreateWindow("Metal Gear Versus", state.width, state.height, SDL_WINDOW_RESIZABLE);
    if (!state.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error Creating Window", nullptr);
        printf("Error Creating Window\n");
        cleanup(state);
        initSuccess = false;
    }

    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error Creating Renderer", nullptr);
        printf("Error Creating Renderer\n");
        cleanup(state);
        initSuccess = false;
    }
    state.keys = SDL_GetKeyboardState(nullptr);

    state.fs.prevTime = SDL_GetTicks();
    state.fs.nowTime = SDL_GetPerformanceCounter();

    //SDL_SetRenderVSync(state.renderer, 1);

    SDL_SetWindowRelativeMouseMode(state.window, true); // mouse 

    // configure presentation
    SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return initSuccess;
}


void cleanup(SDLState &state) {
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void advanceTime(SDLState &state) { // run deltaTime logic
    FrameState &fs = state.fs;
    fs.prevTime = fs.nowTime;
    fs.nowTime = SDL_GetPerformanceCounter(); // take time from previous frame to calculate delta
    
    uint64_t freq = SDL_GetPerformanceFrequency();
    fs.deltaTime = (float)(fs.nowTime - fs.prevTime) / (float)freq;

    const float MAX_TIME = 0.25f;
    if (fs.deltaTime > MAX_TIME) { // spiral of death
        fs.deltaTime = MAX_TIME;
    };

    fs.frames++;
    if (fs.nowTime - fs.lastTime >= freq) { // fps counter
        fs.lastTime = fs.nowTime;
        fs.FPS = fs.frames;           
        fs.frames = 0;
    }
}
