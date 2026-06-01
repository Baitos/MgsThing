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

int main(int argc, char** argv) { 
    SDLState state;
    Resources res;
    // setup state, res 
    init(state, res);
    // setup game state
    GameState gs(state, res);

    // start game loop
    while (running) {
        advanceTime(state);
 
        input(state, gs);
        update(state, gs, res);
        draw(state, gs, res);
    }
    
    res.unload();
    cleanup(state);
    return 0;
}