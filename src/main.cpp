#include <stdio.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <vector>
#include <string>
#include <array>
#include <iostream>

#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/resources.h"
#include "../include/globals.h"
#include "../include/init.h"

#include "../include/input.h"
#include "../include/update.h"
#include "../include/draw.h"

#include "../include/object.h"
#include "../include/player.h"
#include "../include/camera.h"

int main(int argc, char** argv) { 
    SDLState state;
    Resources res;
    // setup state, res 
    init(state, res);
    // set up camera
    Camera cam(state);
    // setup game state
    GameState gs(state, res);
    GameState snapshot = gs;
    // start game loop
    
    while (running) {
        advanceTime(state);
        input(state, gs);

        if (state.im.inputState.pressed & Save) { // testing purposes
            snapshot = gs;
        }
        else if (state.im.inputState.pressed & Restore) {
            gs = snapshot;
        }

        while (state.fs.accumulator >= TICK_RATE) {
            update(state, gs, res, cam, TICK_RATE);
            state.fs.accumulator -= TICK_RATE;
        }
        
        double alpha = state.fs.accumulator / TICK_RATE; // will be for lerping later
        draw(state, gs, res, cam);
    }
    
    res.unload();
    cleanup(state);
    return 0;
}