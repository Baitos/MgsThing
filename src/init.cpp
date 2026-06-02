#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "../include/init.h"
#include "../include/state.h"
#include "../include/resources.h"

bool init(SDLState &state, Resources &res) {
    if (!initialize(state)) {
        return 1;
    }
    
    // load game assets
    res.load(state);

    // set window icon
    SDL_Surface *icon = IMG_Load("data/logo.png");
    SDL_SetWindowIcon(state.window, icon);
    SDL_DestroySurface(icon);

    srand(time(0)); // randomize seed
    return 0;
}