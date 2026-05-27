#include <SDL3/SDL.h>
#include <format>

#include "../include/draw.h"
#include "../include/state.h"
#include "../include/gameState.h"


void draw(const SDLState& state, GameState& gs) {
    SDL_SetRenderDrawColor(state.renderer, 64, 51, 83, 255); // draw background
    SDL_RenderClear(state.renderer);

    gs.player.draw(state, gs);    
    
    if (gs.debugMode) {
    // debug info
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(state.renderer, 5, 5,
                        std::format("FPS: {}", 
                        static_cast<int>(state.fs.FPS)).c_str());
    }



    //swap buffers and present
    SDL_RenderPresent(state.renderer);
}

