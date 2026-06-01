#include <SDL3/SDL.h>
#include <stdio.h>

#include "../include/state.h"
#include "../include/globals.h"
#include "../include/gameState.h"

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
    fs.nowTime = SDL_GetTicks(); // take time from previous frame to calculate delta
    fs.frames++;
    if (fs.nowTime > fs.lastTime + 1000) { // fps counter
        fs.lastTime = fs.nowTime;
        fs.FPS = fs.frames;           
        fs.frames = 0;
    }
    fs.deltaTime = (fs.nowTime - fs.prevTime) / 1000.0f; // convert to seconds from ms
}
