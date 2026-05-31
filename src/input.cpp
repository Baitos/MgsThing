#include <SDL3/SDL.h>

#include "../include/globals.h"
#include "../include/gameState.h"
#include "../include/input.h"
#include "../include/state.h"

#include <iostream>
#include <bitset>

void input(SDLState& state, GameState& gs, const Resources& res) {
    SDL_Event event { 0 };
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
            {
                running = false;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: 
            {
                state.width = event.window.data1;
                state.height = event.window.data2;
                
                //printf("Width = %d, Height = %d", state.width, state.height);
                break;
            }
            case SDL_EVENT_KEY_DOWN:
            {
                if (event.key.scancode == SDL_SCANCODE_F12) {
                    gs.debugMode = !gs.debugMode;
                }
                else if (event.key.scancode == SDL_SCANCODE_F1) {
                    running = false;
                }
                break;
            }
        }
    }
    state.im.handleInput(state.keys);
}

void InputManager::handleInput(const bool *keys) {
    InputState& is = this->inputState;
    uint32_t previous = is.current; // save prev frame
    
    is.current = 0; // reset current inputs

    // using bitwise, add current inputs as bits 
    if (keys[SDL_SCANCODE_W]) {
        is.current |= Up; 
    }
    if (keys[SDL_SCANCODE_S]) {
        is.current |= Down;
    }
    if (keys[SDL_SCANCODE_A]) {
        is.current |= Left;
    }
    if (keys[SDL_SCANCODE_D]) {
        is.current |= Right;
    }
    if (keys[SDL_SCANCODE_LSHIFT]) {
        is.current |= Strafe;
    }

    // newly pressed buttons are anything current and anything not previously pressed
    is.pressed = is.current & ~previous;

    // newly released buttons are anything previous and currently not held
    is.released = previous & ~is.current;

    //std::cout << "Current: " << std::bitset<32>(is.current) << std::endl;

}