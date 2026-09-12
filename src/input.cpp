#include <SDL3/SDL.h>

#include "../include/globals.h"
#include "../include/gameState.h"
#include "../include/input.h"
#include "../include/state.h"

#include <bitset>
#include <iostream>

void input(SDLState& state, GameState& gs) {
    InputState& is = state.im.inputState;
    uint32_t previous = is.current; // save prev frame
    //is.pressed = is.released = 0;
    
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
                state.im.handleInput(event.key.scancode, true); // add current input
                // newly pressed buttons are anything current and anything not previously pressed
                //is.pressed |= is.current & ~previous;
                //previous = is.current; // update previous
                break;
            }
            case SDL_EVENT_KEY_UP:
            {
                state.im.handleInput(event.key.scancode, false); // remove inputs
                // newly released buttons are anything previous and currently not held
                //is.released |= previous & ~is.current;
                //previous = is.current; // update previous
                break;
            }
        }
    }

    //is.pressed = is.current & ~previous;
    //is.released = previous & ~is.current;
    std::cout << "current:  " << std::bitset<8>(is.current) << "\npressed:  " << std::bitset<8>(is.pressed) << "\nreleased: " << std::bitset<8>(is.released) << "\n\n";
    //state.im.handleInput(state.keys);
}

void useInput(SDLState& state, GameState& gs) {

}

const inputTable inpTable[] = {
    {SDL_SCANCODE_W, Up},
    {SDL_SCANCODE_S, Down},
    {SDL_SCANCODE_A, Left},
    {SDL_SCANCODE_D, Right},
    {SDL_SCANCODE_LSHIFT, Strafe},
    {SDL_SCANCODE_LCTRL, Lock},
    {SDL_SCANCODE_F2, Save},
    {SDL_SCANCODE_F3, Restore}
};



void InputManager::handleInput(SDL_Scancode& key, bool keyDown) {

    for (int i = 0; i < std::size(inpTable); i++) {
        if (key == inpTable[i].key) {
            if (keyDown) {
                this->inputState.current |= inpTable[i].input; // add input

                this->inputState.pressed |= inpTable[i].input; // add to pressed
            } else {
                this->inputState.current &= ~inpTable[i].input; // remove input

                this->inputState.released |= inpTable[i].input; // add to released
            }
        }
    }
}